

big_header_template = "<h3 style='margin-bottom: 5px;'> {} </h3>"
small_header_template = "<h4 style='margin-bottom: 5px;'> {} </h4>"

td_template = "<td style='text-align:left;vertical-align:middle'> {} </td>"
tr_template = "<tr> {} </tr>"
th_multi_template = "<th style='text-align: left;' colspan='{}'> {} </th>"
th_single_template = "<th style='text-align: left;'>  {} </th>"
thead_template = "<thead> {} </thead>"
tb_template = "<table style='margin-top: 0px;'>\n {} \n</table>"

div_adjacent_template = "<div style='margin: 0 30px 0 0; float:left;' > {} </div>"
# div_block_template = "<div style='margin: 0 30px 0 0; display: block;' > {} </div>"
div_block_template = "<div style='display: block; margin-top: 20px; margin-bottom: 20px; clear: both;'> {} </div>"
div_clear = "<div style='clear: both; height: 20px;'> </div>"

slideshow_div_template = """
<div id="frame-{}-{}" style="display:{}">
<h3 style='margin-bottom: 5px;'> {} </h3>
{}
</div>
"""

slideshow_buttons_template = """
<br>
<button onclick = "slideshow_{}.first()">
First
</button>
<button onclick = "slideshow_{}.prev()">
Previous
</button>
<button onclick = "slideshow_{}.next()">
Next
</button>
<button onclick = "slideshow_{}.last()">
Last
</button>
<br>
"""

slideshow_js_template = """
<script>
function slideshow(ident, total_frames) {{
 this.i = 0;
 this.t = total_frames;
 this.ident = ident;
 this.animate = function(i, j) {{
  document.getElementById("frame-" + this.ident + "-" + i).style.display = "none";
  document.getElementById("frame-" + this.ident + "-" + j).style.display = "block";
 }}
 this.first = function() {{
  var j = 0;
  this.animate(this.i, j);
  this.i = j;
 }}
 this.next = function() {{
  var j = (this.i + 1) % this.t;
  this.animate(this.i, j);
  this.i = j;
 }}
 this.prev = function() {{
  var j = (this.i - 1 + this.t) % this.t;
  this.animate(this.i, j);
  this.i = j;
 }}
 this.last = function() {{
  var j = this.t - 1;
  this.animate(this.i, j);
  this.i = j;
 }}
}}
var slideshow_{} = new slideshow('{}', {});
</script>
"""

def make_td(content):
    return td_template.format(content)

def make_tr(content):
    return tr_template.format(content)

def make_buffer_label(name):
    return small_header_template.format(name)

def make_header(content):
    return big_header_template.format(content)

def make_block_div(content):
    return div_block_template.format(content)

def make_header_for_table(table, title):
    return div_adjacent_template.format(make_buffer_label(title) + '\n' + table)

def make_table(content, headers=None, title=None):
    """
    :headers: List of (colspan, header) pairs or string
    :return: HTML table as string
    """

    if headers is None:
        table = tb_template.format(content)
    else:
        try:
            iter(headers)
            header_content = " ".join([th_multi_template.format(colspan, header)
                                       for (colspan, header) in headers])
        except TypeError:
            # not iterable
            if isinstance(headers, str):
                header_content += th_single_template.format(headers)
            else:
                raise TypeError("headers must be iterable in the form [(colspan, header)] or a single string.")

        header_html = thead_template.format(header_content)
        table = tb_template.format(header_html + '\n' + content)

    if title:
        return make_header_for_table(table, title)
    else:
        return div_adjacent_template.format('\n' + table)

def make_slideshow_frame(id, content, label, n):
    disp = "block" if n == 0 else "none"
    return slideshow_div_template.format(id, n, disp, label, content)

def make_slideshow(id, total_frames):
    return slideshow_buttons_template.format(*(id,) * 4) + '\n' + \
           slideshow_js_template.format(id, id, total_frames)

