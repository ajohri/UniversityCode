char recursive_fucnt(char * in, int prefix, int count, const char * hash) {
	if(prefix >= strlen(in)) {
		const char * out = crypt_r(in, xx, &crypt_r);
		*count += 1;
		int z = strcmp(out, hash);
		if(z == 0) {
			return in;
		} else {
			return NULL;
		}
	}
	for(int x = 'a'; x <= 'z'; x++) {
		in[prefix] = x;
		if(recursive_funct(in, prefix + 1, count, hash)) {
			return in;
		}
	}
	return NULL;
}