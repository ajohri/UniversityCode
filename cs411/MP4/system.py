# framework for MP on query processing

from IPython.display import HTML, display
import htmlutils

class Singleton(object):
    _instance = None
    def __new__(cls, *args, **kwargs):
        if cls._instance is None:
            cls._instance = super(Singleton, cls).__new__(cls)
            return cls._instance
        else:
            raise RuntimeError("Singleton class can only be instantiated once")

# TODO: make this work with keyword arguments
def type_check(*types):
    error_msg = "Parameter %s is not of type %s in function %s"
    def wrapper(f):
        def wrapper_(*args, **kwargs):
            for arg, typ in zip(args, types):
                if typ is None:
                    pass
                elif type(typ) is str and \
                   getattr(type(arg), "type_name", None) == typ:
                    pass
                elif isinstance(typ, (type, tuple)) and isinstance(arg, typ):
                    pass
                else:
                    raise TypeError(error_msg % (arg, typ, f.__qualname__))
            return f(*args, **kwargs)
        wrapper_.__doc__ = f.__doc__
        return wrapper_
    return wrapper


class Storage(Singleton):
    def __init__(self, max_size):
        self.max_size = max_size
        self.__objects = []
        self.system = None

    def size(self):
        """number of blocks occupied in the storage system"""
        return sum([o.size() for o in self.__objects])

    def _check(self):
        # check that the storage object does not violate any expected conditions
        assert self.size() <= self.max_size, \
               "Max size exceeded for " + self.type_name

    def contains(self, obj):
        """check if the storage system contains the object"""
        return obj in self.__objects

    def clear(self):
        """clear all objects from memory"""
        for obj in self.__objects:
            obj.clear()
        self.__objects.clear()

    def add_clustered_relation(self, relation, name = None):
        """requires at least one block to be available in main memory"""
        buffer = Buffer(self, name = name)
        mem_buffer = memory.new_buffer()
        block = mem_buffer.new_empty_block()
        for row in relation:
            if block.is_full():
                buffer.append_block(block)
                mem_buffer.clear()
                block = mem_buffer.new_empty_block()
            block.append_new_tuple(row)
        if not block.is_empty():
            buffer.append_block(block)
        mem_buffer.clear()
        memory.remove_buffer(mem_buffer)
        self.__objects.append(buffer)
        self._check()
        return buffer

    def add_nonclustered_relation(self, relation, name = None):
        """requires at least one block to be available in main memory"""
        buffer = Buffer(self, name = name)
        mem_buffer = memory.new_buffer()
        for row in relation:
            block = mem_buffer.new_empty_block()
            block.append_new_tuple(row)
            buffer.append_block(block)
            mem_buffer.clear()
        memory.remove_buffer(mem_buffer)
        self.__objects.append(buffer)
        self._check()
        return buffer

    @type_check(None, int)
    def new_buffer(self, size = 0, name = None):
        """create a new empty buffer"""
        if name is None:
            name = "Buffer #" + str(len(self.__objects))
        buffer = Buffer(self, name = name)
        for _ in range(size):
            buffer.new_empty_block()
        self.__objects.append(buffer)
        self._check()
        return buffer

    @type_check(None, "Buffer")
    def remove_buffer(self, buffer):
        self.__objects.remove(buffer)
        self._check()

    def __repr__(self):
        return repr(self.__objects)


class MainMemory(Storage):
    type_name = "MainMemory"
    
    def __init__(self, max_size):
        super(MainMemory, self).__init__(max_size)
        self.__temp_buffer = Buffer(self, name = "Temp buffer")
        self.__temp_buffer.new_empty_block().append_new_tuple((0, ))

    def _check(self):
        assert self.__temp_buffer.size() <= 1 and \
               len(self.__temp_buffer[0]) <= 1, \
               "Temporary buffer cannot hold more than one block / one tuple"
        super(MainMemory, self)._check()

    def contains(self, obj):
        return self.__temp_buffer is obj or \
               super(MainMemory, self).contains(obj)

    def set_temp_to_attr_value(self, attr_value):
        if len(self.__temp_buffer[0][0]) > 0:
            self.__temp_buffer[0][0][0] = attr_value
        else:
            self.__temp_buffer[0][0].append_attr(attr_value)
        return self.__temp_buffer[0][0][0]

    def set_temp_to_tuple_value(self, tuple_value):
        self.__temp_buffer[0].clear()
        self.__temp_buffer[0].new_empty_tuple()
        for a in tuple_value:
            self.__temp_buffer[0][0].append_attr(a)
        return self.__temp_buffer[0][0]

    def show(self):
        display(HTML(data = self._repr_html_()))

    def _repr_html_(self):
        content = []
        content.append(self.__temp_buffer._repr_html_())
        for i, buffer in enumerate(self._Storage__objects):
            content.append(buffer._repr_html_())
        content = '\n'.join(content)
        header = htmlutils.make_header("Main Memory [%i/%i blocks used]" % \
                                       (int(self.size()), int(self.max_size)))
        content = htmlutils.make_block_div(header + '\n' + content)
        return content

    
class Disk(Storage):
    type_name = "Disk"
    def __init__(self, max_size):
        super(Disk, self).__init__(max_size)

    def show(self):
        display(HTML(data = self._repr_html_()))

    def _repr_html_(self):
        content = []
        for i, buffer in enumerate(self._Storage__objects):
            content.append(buffer._repr_html_())
        content = '\n'.join(content)
        header = htmlutils.make_header("Disk [%i/%i blocks used]" % \
                                       (int(self.size()), int(self.max_size)))
        content = htmlutils.make_block_div(header + '\n' + content)
        return content


class System:
    type_name = "System"
    
    def __init__(self, memory, disk):
        self.memory = memory
        memory.system = self
        self.disk = disk
        disk.system = self
        self.__io = 0

    def inc_io_cost(self):
        self.__io += 1

    def get_io_cost(self):
        return self.__io

    def reset_io_cost(self, passcode):
        self.__io = 0

    def clear(self):
        self.reset_io_cost(passcode = "")
        self.memory.clear()
        self.disk.clear()

    def __repr__(self):
        return "Memory\n" + str(self.memory) + "\nDisk\n" + str(self.disk)

    def show(self):
        display(HTML(data = self._repr_html_()))

    def _repr_html_(self):
        return self.memory._repr_html_() + '\n' + \
               htmlutils.make_block_div("&nbsp;") + '\n' + \
               self.disk._repr_html_()


class Slideshow:
    type_name = "Slideshow"

    def __init__(self, system):
        self.__sys = system
        self.__frames = []

    def record(self, label = None):
        if label == None:
            label = "Frame #" + str(len(self.__frames))
        else:
            label = str(len(self.__frames)) + ". " + label
        self.__frames.append((label, self.__sys._repr_html_()))

    def clear(self):
        self.__frames.clear()

    def show(self):
        display(HTML(data = self._repr_html_()))

    def _repr_html_(self):
        id = hex(sum([hash(label) for (label, _) in self.__frames]))[-8 :]
        html = ""
        html += htmlutils.make_slideshow(id, len(self.__frames))
        for i, (label, frame) in enumerate(self.__frames):
            html += htmlutils.make_slideshow_frame(id, frame, label, i)
        return html


# objects

class Attribute:
    """An attribute of a tuple. Must be stored in one (and only one) tuple. 
       Attributes are restricted in the range of values they can have.
       Can use in-place operations to modify Attribute.
    """
    type_name = "Attribute"

    def __init__(self, value, tup):
        assert type(tup) is Tuple, "Attribute must be contained in a tuple"
        self._tuple = tup
        self.set_value(value)

    def _check_value(self):
        # check that value of attribute obey constraints
        a = self.__value
        if type(a) is int:
            assert 0 <= a < 2 ** 16, \
                   "Overflow / underflow for int attribute: " + str(a)
        elif type(a) is str:
            lowers = "".join([chr(x) for x in range(ord('a'), ord('z') + 1)])
            numbers = "".join([chr(x) for x in range(ord('0'), ord('9') + 1)])
            specials = " .,?"
            charset = lowers + numbers + specials
            assert len(a) <= 3 and all([c in charset for c in a]), \
                   "str attribute does not conform to constraints: " + a
        else:
            assert False, "Attributes of tuple must be either int or str"

    def _check_stored_in_tuple(self):
        # check that this attribute is actually contained in its tuple
        assert self._tuple.contains(self), \
               "Attribute must be stored in its containing tuple"

    def _check(self):
        self._check_value()
        self._check_stored_in_tuple()

    def _check_in_main_memory(self, other = None):
        """check if this attr and optionally another attr is in main memory"""
        self._check()
        self._tuple._check_in_main_memory()
        if other and type(other) is Attribute:
            other._check_in_main_memory()

    def _get_value(self, passcode):
        assert passcode == "", \
               "Directly accessing attribute value is illegal"
        return self.__value

    def set_value(self, value):
        if type(value) is Attribute:
            value = value.__value
        self.__value = value
        self._check_value()

    def __extract_value(self, other):
        assert type(other) in [Attribute, int, str], \
               "Wrong type for attribute: " + str(other)
        return other.__value if type(other) is Attribute else other

    def __eq__(self, other):
        self._check_in_main_memory(other)
        return self.__value == self.__extract_value(other)

    def __ne__(self, other):
        self._check_in_main_memory(other)
        return self.__value != self.__extract_value(other)

    def __ge__(self, other):
        self._check_in_main_memory(other)
        return self.__value >= self.__extract_value(other)

    def __gt__(self, other):
        self._check_in_main_memory(other)
        return self.__value > self.__extract_value(other)

    def __le__(self, other):
        self._check_in_main_memory(other)
        return self.__value <= self.__extract_value(other)

    def __lt__(self, other):
        self._check_in_main_memory(other)
        return self.__value < self.__extract_value(other)

    def __add__(self, other):
        self._check_in_main_memory(other)
        return self._tuple._block._container.storage.set_temp_to_attr_value(
            self.__value + self.__extract_value(other))

    def __sub__(self, other):
        self._check_in_main_memory(other)
        return self._tuple._block._container.storage.set_temp_to_attr_value(
            self.__value - self.__extract_value(other))

    def __mul__(self, other):
        self._check_in_main_memory(other)
        return self._tuple._block._container.storage.set_temp_to_attr_value(
            self.__value * self.__extract_value(other))

    def __truediv__(self, other):
        self._check_in_main_memory(other)
        return self._tuple._block._container.storage.set_temp_to_attr_value(
            self.__value / self.__extract_value(other))

    def __floordiv__(self, other):
        self._check_in_main_memory(other)
        return self._tuple._block._container.storage.set_temp_to_attr_value(
            self.__value // self.__extract_value(other))

    def __iadd__(self, other):
        self._check_in_main_memory(other)
        self.__value += self.__extract_value(other)
        return self

    def __isub__(self, other):
        self._check_in_main_memory(other)
        self.__value -= self.__extract_value(other)
        return self

    def __imul__(self, other):
        self._check_in_main_memory(other)
        self.__value *= self.__extract_value(other)
        return self

    def __itruediv__(self, other):
        self._check_in_main_memory(other)
        self.__value /= self.__extract_value(other)
        return self

    def __ifloordiv__(self, other):
        self._check_in_main_memory(other)
        self.__value //= self.__extract_value(other)
        return self

    def __hash__(self):
        return hash(self.__value)

    def show(self):
        display(HTML(data = self._repr_html_()))

    def _repr_html_(self):
        typ = "int" if type(self.__value) is int else "str"
        return str(self.__value)

    def __repr__(self):
        return repr(self.__value)

class Tuple:
    """A tuple that may store a limited number of attributes.
       Must be stored in a block.
       Can only be accessed when block containing the tuple is in main memory.
       Contents of the tuple can not be read, but can be printed. 
    """
    type_name = "Tuple"
    MAX_ATTRS_PER_TUPLE = 4

    def __init__(self, values, block):
        assert type(block) is Block, "Tuple must be contained in a buffer"
        self._block = block
        if isinstance(values, (int, str)):
            values = (values, )
        self.__attrs = tuple([Attribute(v, self) for v in values])
        
        self._check_values()

    def _check_values(self):
        # check that attributes obey constraints
        assert type(self.__attrs) is tuple, \
               "Attributes should be stored as a tuple"
        assert len(self.__attrs) <= self.MAX_ATTRS_PER_TUPLE, \
               "Maximum number of attributes exceeded"
        for a in self.__attrs:
            assert type(a) is Attribute, \
                   "Tuple can only store attributes of the Attribute class"
            a._check_value()

    def _check_stored_in_block(self):
        # check that this tuple is actually contained in its block
        assert self._block.contains(self), \
               "Tuple must be stored in its containing block"

    def _check(self):
        self._check_values()
        self._check_stored_in_block()
        
    def _check_in_main_memory(self, other = None):
        """check if this tuple and optionally another tuple is in main memory"""
        self._check()
        self._block._check_in_main_memory()
        if other and type(other) is Tuple:
            other._check_in_main_memory()

    def append_attr(self, attr):
        self._check_in_main_memory()
        self.__attrs += (Attribute(attr, tup = self), )
        self._check()

    def contains(self, obj):
        return any([t is obj for t in self.__attrs])

    def is_empty(self):
        return len(self.__attrs) == 0

    def is_full(self):
        return len(self.__attrs) >= self.MAX_ATTRS_PER_TUPLE

    def combine(self, other):
        """Concatenate two tuples and return result as temp tuple. """
        self._check_in_main_memory(other)
        tmp = self._block._container.storage.set_temp_to_tuple_value(self)
        for a in self.__extract_attrs(other):
            tmp.append_attr(a)
        tmp._check()
        return tmp

    @type_check("Tuple", "Tuple")
    def combine_with(self, other):
        """Concatenate this tuple with another tuple. In-place operation. """
        self._check_in_main_memory(other)
        for a in self.__extract_attrs(other):
            self.append_attr(a)
        self._check()
        return self

    def _get_values(self, passcode):
        assert passcode == "", \
               "Directly accessing tuple values is illegal"
        return tuple([attr._get_value(passcode) for attr in self.__attrs])

    def __extract_attrs(self, other):
        assert type(other) in [Tuple, tuple], \
               "Wrong type for tuple: " + str(other)
        return other.__attrs if type(other) is Tuple else other

    @type_check("Tuple", "Tuple")
    def __eq__(self, other):
        self._check_in_main_memory(other)
        return self.__attrs == self.__extract_attrs(other)

    @type_check("Tuple", "Tuple")
    def __ne__(self, other):
        self._check_in_main_memory(other)
        return self.__attrs != self.__extract_attrs(other)

    @type_check("Tuple", "Tuple")
    def __ge__(self, other):
        self._check_in_main_memory(other)
        return self.__attrs >= self.__extract_attrs(other)

    @type_check("Tuple", "Tuple")
    def __gt__(self, other):
        self._check_in_main_memory(other)
        return self.__attrs > self.__extract_attrs(other)

    @type_check("Tuple", "Tuple")
    def __le__(self, other):
        self._check_in_main_memory(other)
        return self.__attrs <= self.__extract_attrs(other)

    @type_check("Tuple", "Tuple")
    def __lt__(self, other):
        self._check_in_main_memory(other)
        return self.__attrs < self.__extract_attrs(other)

    def __getitem__(self, key):
        self._check_in_main_memory()
        storage = self._block._container.storage
        if type(key) is int:
            return self.__attrs[key]
        elif hasattr(key, "__iter__") and all([type(k) is int for k in key]):
            subvals = [v for i, v in enumerate(self.__attrs) if i in key]
            return storage.set_temp_to_tuple_value(subvals)

    @type_check("Tuple", int, (int, str, Attribute))
    def __setitem__(self, key, item):
        self._check_in_main_memory()
        self.__attrs[key].set_value(Attribute(item, tup = self))
        return self.__attrs[key]

    def __len__(self):
        self._check_in_main_memory()
        return len(self.__attrs)

    def __hash__(self):
        return sum([(123 ** i) * hash(a) for i, a in enumerate(self.__attrs)])

    def show(self):
        display(HTML(data = self._repr_html_()))

    def _repr_html_(self):
        return "(" + ", ".join([v._repr_html_() for v in self.__attrs]) + ")"

    def __repr__(self):
        return "Tuple(" + repr(self.__attrs) + ")"

class Block(list):
    """Stores a list of tuples in either main memory or disk.
       Represents a basic unit of storage.
       Can be stored in buffer, hashtable, or index. 
       Can be moved in between main memory and disk.
    """
    type_name = "Block"
    TUPLES_PER_BLOCK = 5

    def __init__(self, container):
        assert type(container) is Buffer, \
               "Block can only be contained in a buffer"
        self._container = container

    def insert_tuple(self, index, tuple_value):
        if type(tuple_value) is not Tuple:
            self.insert_new_tuple(index, tuple_value)
        else:
            self.insert_copy_of_tuple(index, tuple_value)

    def append_tuple(self, tuple_value):
        self.insert_tuple(len(self), tuple_value)

    @type_check("Block", int, None)
    def insert_new_tuple(self, index, tuple_value):
        self._check_in_main_memory()
        super(Block, self).insert(index, Tuple(tuple_value, block = self))
        self._container.storage._check()
        self._check()

    def append_new_tuple(self, tuple_value):
        self.insert_new_tuple(len(self), tuple_value)

    @type_check("Block", int, "Tuple")
    def insert_copy_of_tuple(self, index, t):
        self._check_in_main_memory()
        t._check_in_main_memory()
        t_ = Tuple(t._get_values(passcode = ""), self)
        super(Block, self).insert(index, t_)
        self._container.storage._check()
        self._check()

    @type_check("Block", "Tuple")
    def append_copy_of_tuple(self, t):
        self.insert_copy_of_tuple(len(self), t)

    def insert_new_empty_tuple(index, self):
        self.insert_new_tuple(index, [])
        return self[index]

    def new_empty_tuple(self):
        self.append_new_tuple([])
        return self[-1]

    def contains(self, obj):
        return any([t is obj for t in self])

    def is_empty(self):
        return len(self) == 0

    def is_full(self):
        return len(self) >= self.TUPLES_PER_BLOCK

    def _check(self):
        # check that this block is actually contained in a buffer
        assert self._container.contains(self), \
               "Block must be stored in its container"

        # check that the number of tuples in this block is valid
        assert len(self) <= self.TUPLES_PER_BLOCK, \
               "Maximum number of tuples in block exceeded: " + str(self)

    def _check_in_main_memory(self, other = None):
        """check if this block is in main memory"""
        self._check()
        assert type(self._container.storage) is MainMemory, \
               "Block must be in main memory"
        if other:
            other._check_in_main_memory()

    def show(self):
        display(HTML(data = self._repr_html_()))

    def _to_html(self, show_index = False):
        content = "\n".join([htmlutils.make_td(t._repr_html_()) for t in self])
        return htmlutils.make_tr(content)
    
    def _repr_html_(self):
        return htmlutils.make_table(self._to_html())

class Buffer(list): #TODO: store list instead of subclassing
    """A contiguous, ordered list of blocks in memory or disk"""
    type_name = "Buffer"
    
    def __init__(self, storage, name = None):
        self.storage = storage
        self.name = name

    def new_empty_block(self):
        block = Block(self)
        super(Buffer, self).append(block)
        return block

    def insert_copy_of_block(self, index, block):
        assert not(type(self.storage) is Disk and
                   type(block._container.storage) is Disk), \
               "Cannot move a block from disk to disk"
        if type(self.storage) != type(block._container.storage):
            self.storage.system.inc_io_cost()
        block2 = Block(block._container)
        block2._container = self
        super(Buffer, self).insert(index, block2)
        for t in block:
            block2.append(Tuple(t._get_values(passcode = ""), block2))
        self.storage._check()
        self._check()

    def append_block(self, block):
        self.insert_copy_of_block(len(self), block)

    def append_copy_of_block(self, block):
        self.append_block(block)

    def add_copy_of_tuple(self, t):
        block = self[-1] if len(self) > 0 and not self[-1].is_full() else \
                self.new_empty_block()
        block.append_copy_of_tuple(t)
        return block[-1]

    def new_empty_tuple(self):
        block = self[-1] if len(self) > 0 and not self[-1].is_full() else \
                self.new_empty_block()
        block.new_empty_tuple()
        return block[-1]

    def append_to(self, buffer, start = 0, times = -1):
        times = len(self) if times == -1 else times
        for i in range(times):
            buffer.append_block(self[start + i])

    def write_to(self, buffer, start = 0, times = -1):
        buffer.clear()
        self.append_to(buffer, start, times)

    def write_block_to(self, buffer, index = 0):
        self.write_to(buffer, start = index, times = 1)

    def read_from(self, buffer, start = 0, times = -1):
        buffer.write_to(self, start, times)

    def read_block_from(self, buffer, index = 0):
        buffer.write_block_to(self, index)

    @type_check("Buffer", Storage)
    def move_to(self, new_storage):
        """Move buffer to new storage container. NOT an in-place operation. """
        if self.storage != new_storage:
            buffer2 = new_storage.new_buffer(name = self.name)
            self.write_to(buffer2)
            self.clear()
            self.storage.remove_buffer(self)
            return buffer2

    def iterate_over_all_tuples(self):
        for b in self:
            for t in b:
                yield t

    def size(self):
        return len(self)

    def contains(self, obj):
        return any([block is obj for block in self])

    def _check_in_main_memory(self):
        assert type(self.storage) is MainMemory, \
               "Cannot directly access buffer while it is stored on disk"

    def _check(self):
        # verify that the buffer is contained in main memory or disk
        assert self.storage is memory or self.storage is disk, \
               "Block must be contained in main memory or disk"
        
        # verify that buffer does not violate any expected conditions
        for block in self:
            assert block._container == self, \
                   "Block with value " + str(block) + \
                   " does not belong to this buffer"

    def show(self):
        display(HTML(data = self._repr_html_()))

    def _to_html(self, show_index=False):
        if show_index:
            content = []
            for (i, block) in enumerate(self):
                html = block._to_html(show_index)
                p = html.find("<tr>") + 4
                html = html[:p] + htmlutils.make_td(i) + html[p:]
                content.append(html)
            return "\n".join(content)
        else:
            return "\n".join(block._to_html() for block in self)

    def _repr_html_(self):
        content = self._to_html(show_index=True)
        max_length = len(max(self, key=len)) if self.size() > 0 else 1
        headers = [(1, "Block"), (max_length, "Content")]
        tab = htmlutils.make_table(content, headers = headers)
        name = self.name if self.name else "Buffer"
        return htmlutils.make_header_for_table(tab, title = name)

class Index:
    """A mapping from attribute value to a block that contains
       the tuple whose attribute is equal to that value.
       Index is single-dimensional.
    """
    def __init__(self, index):
        # index is stored as a list of tuples: [(value, block, tuple_ind), ...]
        # mapping is many-to-many
        self.__index = index.copy()

    def lookup(self, value):
        """Return a list of pointers to tuples that contain the given value
           Input: value = value of attribute to perform lookup on
           Output: list of (block pointer, tuple index) pairs
        """
        pointers = []
        for v, b, i in self.__index:
            if v == value:
                pointers.append((b, i))
        return pointers

    def lookup_matching_blocks(self, value):
        """Return a list of pointers to blocks containing tuples w/ given value.
           Input: value = value of attribute to perform lookup on
           Output: list of block pointers
        """
        pointers = []
        for val, block, _ in self.__index:
            if not any([id(block) == id(b) for b in pointers]):
                if val == value:
                    pointers.append(block)
        return pointers

    def __iter__(self):
        for entry in self.__index:
            yield entry

# constants
# number of blocks in main memory
M = 10

# number of blocks on disk
D = 100

TUPLES_PER_BLOCK = 5
MAX_ATTRS_PER_TUPLE = 3

# singleton instances
memory = MainMemory(max_size = M)
disk = Disk(max_size = D)
system = System(memory, disk)
slideshow = Slideshow(system)
