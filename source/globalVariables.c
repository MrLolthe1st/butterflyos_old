GlobalVariable * globalTableFirst = 0;
struct rb_tree * globalVarsTree;
int _strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2)
	{
		if (*s1 == '\0')
		{
			return 0;
		}

		++s1;
		++s2;
	}

	return *s1 - *s2;
}
int global_cmp(struct rb_tree *self, struct rb_node *node_a, struct rb_node *node_b) {
	GlobalVariable * v1 = (GlobalVariable*)node_a->value;
	GlobalVariable * v2 = (GlobalVariable*)node_b->value;
	return _strcmp(v1->name, v2->name);
}
void initGlobals()
{
	globalVarsTree = rb_tree_create(global_cmp);

}
void addGlobalVariable(char * name, void * addr)
{
	GlobalVariable * v = (GlobalVariable*)mmalloc(sizeof(GlobalVariable));
	v->name = name;
	v->ptr = (int)addr;
	rb_tree_insert(globalVarsTree, v);
}



int _getcmpstr(char * a, char *b)
{
	while(a&&b&&*a&&*b)
	{
		if(*a!=*b)
			return 0;
	}
	if(a&&b&&((*a)==(*b)))
		return 1;
	return 0;
}

unsigned int getVariableAddress(char * name)
{
	GlobalVariable * v = (GlobalVariable*)mmalloc(sizeof(GlobalVariable));
	v->name = name;
	GlobalVariable * w = rb_tree_find(globalVarsTree, v);
	free(v);
	return w->ptr;
}