void ffree(void * mem);
char * mmalloc(size_t size);
#ifndef AVL_TREE_ENTRIES_COUNT
#define AVL_TREE_ENTRIES_COUNT (1<<20)
#endif
#define NULL 0
#ifndef __RB_TREE_H__
#define __RB_TREE_H__ 1


#ifndef RB_ITER_MAX_HEIGHT
#define RB_ITER_MAX_HEIGHT 64 // Tallest allowable tree to iterate
#endif

struct rb_node;
struct rb_tree;

typedef int(*rb_tree_node_cmp_f) (struct rb_tree *self, struct rb_node *a, struct rb_node *b);
typedef void(*rb_tree_node_f)     (struct rb_tree *self, struct rb_node *node);

struct rb_node {
	int             red;     // Color red (1), black (0)
	struct rb_node *link[2]; // Link left [0] and right [1]
	void           *value;   // User provided, used indirectly via rb_tree_node_cmp_f.
};

struct rb_tree {
	struct rb_node    *root;
	rb_tree_node_cmp_f cmp;
	size_t             size;
	void              *info; // User provided, not used by rb_tree.
};

struct rb_iter {
	struct rb_tree *tree;
	struct rb_node *node;                     // Current node
	struct rb_node *path[RB_ITER_MAX_HEIGHT]; // Traversal path
	size_t          top;                      // Top of stack
	void           *info;                     // User provided, not used by rb_iter.
};

int             rb_tree_node_cmp_ptr_cb(struct rb_tree *self, struct rb_node *a, struct rb_node *b);
void            rb_tree_node_dealloc_cb(struct rb_tree *self, struct rb_node *node);

struct rb_node *rb_node_alloc();
struct rb_node *rb_node_create(void *value);
struct rb_node *rb_node_init(struct rb_node *self, void *value);
void            rb_node_dealloc(struct rb_node *self);

struct rb_tree *rb_tree_alloc();
struct rb_tree *rb_tree_create(rb_tree_node_cmp_f cmp);
struct rb_tree *rb_tree_init(struct rb_tree *self, rb_tree_node_cmp_f cmp);
void            rb_tree_dealloc(struct rb_tree *self, rb_tree_node_f node_cb);
void           *rb_tree_find(struct rb_tree *self, void *value);
int             rb_tree_insert(struct rb_tree *self, void *value);
int             rb_tree_remove(struct rb_tree *self, void *value);
size_t          rb_tree_size(struct rb_tree *self);

int             rb_tree_insert_node(struct rb_tree *self, struct rb_node *node);
int             rb_tree_remove_with_cb(struct rb_tree *self, void *value, rb_tree_node_f node_cb);

int             rb_tree_test(struct rb_tree *self, struct rb_node *root);

struct rb_iter *rb_iter_alloc();
struct rb_iter *rb_iter_init();
struct rb_iter *rb_iter_create();
void            rb_iter_dealloc(struct rb_iter *self);
void           *rb_iter_first(struct rb_iter *self, struct rb_tree *tree);
void           *rb_iter_last(struct rb_iter *self, struct rb_tree *tree);
void           *rb_iter_next(struct rb_iter *self);
void           *rb_iter_prev(struct rb_iter *self);

#endif


struct rb_node *
	rb_node_alloc() {
	return mmalloc(sizeof(struct rb_node));
}

struct rb_node *
	rb_node_init(struct rb_node *self, void *value) {
	if (self) {
		self->red = 1;
		self->link[0] = self->link[1] = NULL;
		self->value = value;
	}
	return self;
}

struct rb_node *
	rb_node_create(void *value) {
	return rb_node_init(rb_node_alloc(), value);
}

void
rb_node_dealloc(struct rb_node *self) {
	if (self) {
		ffree(self);
	}
}

static int
rb_node_is_red(const struct rb_node *self) {
	return self ? self->red : 0;
}

static struct rb_node *
rb_node_rotate(struct rb_node *self, int dir) {
	struct rb_node *result = NULL;
	if (self) {
		result = self->link[!dir];
		self->link[!dir] = result->link[dir];
		result->link[dir] = self;
		self->red = 1;
		result->red = 0;
	}
	return result;
}

static struct rb_node *
rb_node_rotate2(struct rb_node *self, int dir) {
	struct rb_node *result = NULL;
	if (self) {
		self->link[!dir] = rb_node_rotate(self->link[!dir], !dir);
		result = rb_node_rotate(self, dir);
	}
	return result;
}

// rb_tree - default callbacks

int
rb_tree_node_cmp_ptr_cb(struct rb_tree *self, struct rb_node *a, struct rb_node *b) {
	return (a->value > b->value) - (a->value < b->value);
}

void
rb_tree_node_dealloc_cb(struct rb_tree *self, struct rb_node *node) {
	if (self) {
		if (node) {
			rb_node_dealloc(node);
		}
	}
}

// rb_tree

struct rb_tree *
	rb_tree_alloc() {
	return mmalloc(sizeof(struct rb_tree));
}

struct rb_tree *
	rb_tree_init(struct rb_tree *self, rb_tree_node_cmp_f node_cmp_cb) {
	if (self) {
		self->root = NULL;
		self->size = 0;
		self->cmp = node_cmp_cb ? node_cmp_cb : rb_tree_node_cmp_ptr_cb;
	}
	return self;
}

struct rb_tree *
	rb_tree_create(rb_tree_node_cmp_f node_cb) {
	return rb_tree_init(rb_tree_alloc(), node_cb);
}

void
rb_tree_dealloc(struct rb_tree *self, rb_tree_node_f node_cb) {
	if (self) {
		if (node_cb) {
			struct rb_node *node = self->root;
			struct rb_node *save = NULL;

			// Rotate away the left links so that
			// we can treat this like the destruction
			// of a linked list
			while (node) {
				if (node->link[0] == NULL) {

					// No left links, just kill the node and move on
					save = node->link[1];
					node_cb(self, node);
					node = NULL;
				}
				else {

					// Rotate away the left link and check again
					save = node->link[0];
					node->link[0] = save->link[1];
					save->link[1] = node;
				}
				node = save;
			}
		}
		ffree(self);
	}
}

int
rb_tree_test(struct rb_tree *self, struct rb_node *root) {
	int lh, rh;

	if (root == NULL)
		return 1;
	else {
		struct rb_node *ln = root->link[0];
		struct rb_node *rn = root->link[1];

		/* Consecutive red links */
		if (rb_node_is_red(root)) {
			if (rb_node_is_red(ln) || rb_node_is_red(rn)) {
				kprintf("Red violation");
				return 0;
			}
		}

		lh = rb_tree_test(self, ln);
		rh = rb_tree_test(self, rn);

		/* Invalid binary search tree */
		if ((ln != NULL && self->cmp(self, ln, root) >= 0)
			|| (rn != NULL && self->cmp(self, rn, root) <= 0))
		{
			kprintf("Binary tree violation");
			return 0;
		}

		/* Black height mismatch */
		if (lh != 0 && rh != 0 && lh != rh) {
			kprintf("Black violation");
			return 0;
		}

		/* Only count black links */
		if (lh != 0 && rh != 0)
			return rb_node_is_red(root) ? lh : lh + 1;
		else
			return 0;
	}
}

void *
rb_tree_find(struct rb_tree *self, void *value) {
	void *result = NULL;
	if (self) {
		struct rb_node node = { .value = value };
		struct rb_node *it = self->root;
		int cmp = 0;
		while (it) {
			if ((cmp = self->cmp(self, it, &node))) {

				// If the tree supports duplicates, they should be
				// chained to the right subtree for this to work
				it = it->link[cmp < 0];
			}
			else {
				break;
			}
		}
		result = it ? it->value : NULL;
	}
	return result;
}

// Creates (mmalloc'ates) 
int
rb_tree_insert(struct rb_tree *self, void *value) {
	return rb_tree_insert_node(self, rb_node_create(value));
}

// Returns 1 on success, 0 otherwise.
int
rb_tree_insert_node(struct rb_tree *self, struct rb_node *node) {
	int result = 0;
	if (self && node) {
		if (self->root == NULL) {
			self->root = node;
			result = 1;
		}
		else {
			struct rb_node head = { 0 }; // False tree root
			struct rb_node *g, *t;       // Grandparent & parent
			struct rb_node *p, *q;       // Iterator & parent
			int dir = 0, last = 0;

			// Set up our helpers
			t = &head;
			g = p = NULL;
			q = t->link[1] = self->root;

			// Search down the tree for a place to insert
			while (1) {
				if (q == NULL) {

					// Insert node at the first null link.
					p->link[dir] = q = node;
				}
				else if (rb_node_is_red(q->link[0]) && rb_node_is_red(q->link[1])) {

					// Simple red violation: color flip
					q->red = 1;
					q->link[0]->red = 0;
					q->link[1]->red = 0;
				}

				if (rb_node_is_red(q) && rb_node_is_red(p)) {

					// Hard red violation: rotations necessary
					int dir2 = t->link[1] == g;
					if (q == p->link[last]) {
						t->link[dir2] = rb_node_rotate(g, !last);
					}
					else {
						t->link[dir2] = rb_node_rotate2(g, !last);
					}
				}

				// Stop working if we inserted a node. This
				// check also disallows duplicates in the tree
				if (self->cmp(self, q, node) == 0) {
					break;
				}

				last = dir;
				dir = self->cmp(self, q, node) < 0;

				// Move the helpers down
				if (g != NULL) {
					t = g;
				}

				g = p, p = q;
				q = q->link[dir];
			}

			// Update the root (it may be different)
			self->root = head.link[1];
		}

		// Make the root black for simplified logic
		self->root->red = 0;
		++self->size;
	}

	return 1;
}

// Returns 1 if the value was removed, 0 otherwise. Optional node callback
// can be provided to dealloc node and/or user data. Use rb_tree_node_dealloc
// default callback to deallocate node created by rb_tree_insert(...).
int
rb_tree_remove_with_cb(struct rb_tree *self, void *value, rb_tree_node_f node_cb) {
	if (self->root != NULL) {
		struct rb_node head = { 0 }; // False tree root
		struct rb_node node = { .value = value }; // Value wrapper node
		struct rb_node *q, *p, *g; // Helpers
		struct rb_node *f = NULL;  // Found item
		int dir = 1;

		// Set up our helpers
		q = &head;
		g = p = NULL;
		q->link[1] = self->root;

		// Search and push a red node down
		// to fix red violations as we go
		while (q->link[dir] != NULL) {
			int last = dir;

			// Move the helpers down
			g = p, p = q;
			q = q->link[dir];
			dir = self->cmp(self, q, &node) < 0;

			// Save the node with matching value and keep
			// going; we'll do removal tasks at the end
			if (self->cmp(self, q, &node) == 0) {
				f = q;
			}

			// Push the red node down with rotations and color flips
			if (!rb_node_is_red(q) && !rb_node_is_red(q->link[dir])) {
				if (rb_node_is_red(q->link[!dir])) {
					p = p->link[last] = rb_node_rotate(q, dir);
				}
				else if (!rb_node_is_red(q->link[!dir])) {
					struct rb_node *s = p->link[!last];
					if (s) {
						if (!rb_node_is_red(s->link[!last]) && !rb_node_is_red(s->link[last])) {

							// Color flip
							p->red = 0;
							s->red = 1;
							q->red = 1;
						}
						else {
							int dir2 = g->link[1] == p;
							if (rb_node_is_red(s->link[last])) {
								g->link[dir2] = rb_node_rotate2(p, last);
							}
							else if (rb_node_is_red(s->link[!last])) {
								g->link[dir2] = rb_node_rotate(p, last);
							}

							// Ensure correct coloring
							q->red = g->link[dir2]->red = 1;
							g->link[dir2]->link[0]->red = 0;
							g->link[dir2]->link[1]->red = 0;
						}
					}
				}
			}
		}

		// Replace and remove the saved node
		if (f) {
			void *tmp = f->value;
			f->value = q->value;
			q->value = tmp;

			p->link[p->link[1] == q] = q->link[q->link[0] == NULL];

			if (node_cb) {
				node_cb(self, q);
			}
			q = NULL;
		}

		// Update the root (it may be different)
		self->root = head.link[1];

		// Make the root black for simplified logic
		if (self->root != NULL) {
			self->root->red = 0;
		}

		--self->size;
	}
	return 1;
}

int
rb_tree_remove(struct rb_tree *self, void *value) {
	int result = 0;
	if (self) {
		result = rb_tree_remove_with_cb(self, value, rb_tree_node_dealloc_cb);
	}
	return result;
}

size_t
rb_tree_size(struct rb_tree *self) {
	size_t result = 0;
	if (self) {
		result = self->size;
	}
	return result;
}

// rb_iter

struct rb_iter *
	rb_iter_alloc() {
	return mmalloc(sizeof(struct rb_iter));
}

struct rb_iter *
	rb_iter_init(struct rb_iter *self) {
	if (self) {
		self->tree = NULL;
		self->node = NULL;
		self->top = 0;
	}
	return self;
}

struct rb_iter *
	rb_iter_create() {
	return rb_iter_init(rb_iter_alloc());
}

void
rb_iter_dealloc(struct rb_iter *self) {
	if (self) {
		ffree(self);
	}
}

// Internal function, init traversal object, dir determines whether
// to begin traversal at the smallest or largest valued node.
static void *
rb_iter_start(struct rb_iter *self, struct rb_tree *tree, int dir) {
	void *result = NULL;
	if (self) {
		self->tree = tree;
		self->node = tree->root;
		self->top = 0;

		// Save the path for later selfersal
		if (self->node != NULL) {
			while (self->node->link[dir] != NULL) {
				self->path[self->top++] = self->node;
				self->node = self->node->link[dir];
			}
		}

		result = self->node == NULL ? NULL : self->node->value;
	}
	return result;
}

// Traverse a red black tree in the user-specified direction (0 asc, 1 desc)
static void *
rb_iter_move(struct rb_iter *self, int dir) {
	if (self->node->link[dir] != NULL) {

		// Continue down this branch
		self->path[self->top++] = self->node;
		self->node = self->node->link[dir];
		while (self->node->link[!dir] != NULL) {
			self->path[self->top++] = self->node;
			self->node = self->node->link[!dir];
		}
	}
	else {

		// Move to the next branch
		struct rb_node *last = NULL;
		do {
			if (self->top == 0) {
				self->node = NULL;
				break;
			}
			last = self->node;
			self->node = self->path[--self->top];
		} while (last == self->node->link[dir]);
	}
	return self->node == NULL ? NULL : self->node->value;
}

void *
rb_iter_first(struct rb_iter *self, struct rb_tree *tree) {
	return rb_iter_start(self, tree, 0);
}

void *
rb_iter_last(struct rb_iter *self, struct rb_tree *tree) {
	return rb_iter_start(self, tree, 1);
}

void *
rb_iter_next(struct rb_iter *self) {
	return rb_iter_move(self, 1);
}

void *
rb_iter_prev(struct rb_iter *self) {
	return rb_iter_move(self, 0);
}

#ifndef AVL_TREE_H
#define AVL_TREE_H

typedef struct {
	void* key;
	void* val;
} node_t;

typedef struct {
	/* size of array */
	int size;
	int count;
	long(*cmp)(
		const void *e1,
		const void *e2);
	node_t *nodes;
} avltree_t;

typedef struct {
	int current_node;
} avltree_iterator_t;

avltree_t* avltree_new(long(*cmp)(const void *e1, const void *e2));

void* avltree_remove(avltree_t* me, void* k);

int avltree_count(avltree_t* me);

int avltree_size(avltree_t* me);

int avltree_height(avltree_t* me);

void avltree_empty(avltree_t* me);

void avltree_insert(avltree_t* me, void* k, void* v);

void* avltree_get(avltree_t* me, const void* k);

void* avltree_get_from_idx(avltree_t* me, int idx);

/**
* Rotate on X:
* Y = X's parent
* Step A: Y becomes left child of X
* Step B: X's left child's becomes Y's right child */
void avltree_rotate_left(avltree_t* me, int idx);

/**
* Rotate on X:
* Y = X's left child
* Step A: X becomes right child of X's left child
* Step B: X's left child's right child becomes X's left child */
void avltree_rotate_right(avltree_t* me, int idx);


/**
* Initialise a new hash iterator over this hash
* It is NOT safe to remove items while iterating.  */
void avltree_iterator(avltree_t * h, avltree_iterator_t * iter);

/**
* Iterate to the next item on an iterator
* @return next item key from iterator */
void *avltree_iterator_next(avltree_t * h, avltree_iterator_t * iter);

/**
* Iterate to the next item on an iterator
* @return next item value from iterator */
void *avltree_iterator_next_value(avltree_t * h, avltree_iterator_t * iter);

int avltree_iterator_has_next(avltree_t * h, avltree_iterator_t * iter);

void* avltree_iterator_peek_value(avltree_t * h, avltree_iterator_t * iter);

void* avltree_iterator_peek(avltree_t * h, avltree_iterator_t * iter);

#endif /* AVL_TREE_H */

#define max(x,y) ((x) < (y) ? (y) : (x))

static int __child_l(const int idx)
{
	return idx * 2 + 1;
}

static int __child_r(const int idx)
{
	return idx * 2 + 2;
}

static int __parent(const int idx)
{
#if 0
	if (idx == 0) return *(int*)NULL;
#endif
	//assert(idx != 0);
	return (idx - 1) / 2;
}



avltree_t* avltree_new(long(*cmp)(
	const void *e1,
	const void *e2))
{
	avltree_t* me;

	//assert(cmp);

	//me = calloc(1, sizeof(avltree_t));
	me->size = 40;
	//me->nodes = calloc(me->size, sizeof(node_t));
	me->cmp = cmp;
	return me;
}
void avltree_new1(avltree_t* me, node_t * nodes, long(*cmp)(
	const void *e1,
	const void *e2))
{


	//assert(cmp);

	// me = calloc(1,sizeof(avltree_t));
	me->size = AVL_TREE_ENTRIES_COUNT;
	me->nodes = nodes;
	me->cmp = cmp;
	return me;
}
static int __count(avltree_t* me, int idx)
{
	if (me->size <= idx || !me->nodes[idx].key)
		return 0;
	return __count(me, __child_l(idx)) + __count(me, __child_r(idx)) + 1;
}

int avltree_count(avltree_t* me)
{
	//    return __count(me,0);
	return me->count;
}

int avltree_size(avltree_t* me)
{
	return me->size;
}

static int __height(avltree_t* me, int idx)
{
	if (idx >= me->size || !me->nodes[idx].key) return 0;
	return max(
		__height(me, __child_l(idx)) + 1,
		__height(me, __child_r(idx)) + 1);
}

int avltree_height(avltree_t* me)
{
	return __height(me, 0);
}

static void __shift_up(avltree_t* me, int idx, int towards)
{
	if (!me->nodes[idx].key)
		return;

	memcpy(&me->nodes[towards], &me->nodes[idx], sizeof(node_t));
	me->nodes[idx].key = NULL;
	__shift_up(me, __child_l(idx), __child_l(towards));
	__shift_up(me, __child_r(idx), __child_r(towards));
}

static void __shift_down(avltree_t* me, int idx, int towards)
{
	if (!me->nodes[idx].key || idx >= me->size)
		return;

	__shift_down(me, __child_l(idx), __child_l(towards));
	__shift_down(me, __child_r(idx), __child_r(towards));
	memcpy(&me->nodes[towards], &me->nodes[idx], sizeof(node_t));
}

void avltree_rotate_right(avltree_t* me, int idx)
{
	/* A Partial
	* Move X out of the way so that Y can take its spot */
	__shift_down(me, __child_r(idx), __child_r(__child_r(idx)));
	memcpy(&me->nodes[__child_r(idx)], &me->nodes[idx], sizeof(node_t));

	/* B */
	__shift_down(me, __child_r(__child_l(idx)), __child_l(__child_r(idx)));
	me->nodes[__child_r(__child_l(idx))].key = NULL;

	/* A Final
	* Move Y into X's old spot */
	__shift_up(me, __child_l(idx), idx);
}

void* avltree_get(avltree_t* me, const void* k)
{
	int i;

	for (i = 0; i < me->size; )
	{
		int r;
		node_t *n;

		n = &me->nodes[i];

		/* couldn't find it */
		if (!n->key)
			return NULL;

		r = me->cmp(n->key, k);

		if (r == 0)
		{
			return n->val;
		}
		else if (r < 0)
		{
			i = __child_l(i);
		}
		else if (r > 0)
		{
			i = __child_r(i);
		}
		else
		{
			//assert(0);
		}
	}

	/* couldn't find it */
	return NULL;
}

void* avltree_get1(avltree_t* me, const void* k, const void * v)
{
	int i;

	for (i = 0; i < me->size; )
	{
		int r;
		node_t *n;

		n = &me->nodes[i];

		/* couldn't find it */
		if (!n->key)
			return NULL;

		r = me->cmp(n->key, k);

		if (r == 0)
		{
			if (v<n->val)
				i = __child_l(i);
			else if (v>n->val)
				i = __child_r(i);
			else
				return n->val;
		}
		else if (r < 0)
		{
			i = __child_l(i);
		}
		else if (r > 0)
		{
			i = __child_r(i);
		}
		else
		{
			//assert(0);
		}
	}

	/* couldn't find it */
	return NULL;
}

void* avltree_get_from_idx(avltree_t* me, int idx)
{
	return me->nodes[idx].key;
}

void avltree_rotate_left(avltree_t* me, int idx)
{
	int p;

	p = __parent(idx);

	/* A Partial
	* Move Y out of the way so that X can take its spot */
	__shift_down(me, __child_l(p), __child_l(__child_l(p)));
	memcpy(&me->nodes[__child_l(p)], &me->nodes[p], sizeof(node_t));

	/* B */
	__shift_down(me, __child_l(idx), __child_r(__child_l(p)));
	me->nodes[__child_l(idx)].key = NULL;

	/* A Final
	* Move Y into X's old spot */
	__shift_up(me, idx, p);
}

static void __rebalance(avltree_t* me, int idx)
{

	while (1)
	{
		if (2 <= abs(
			__height(me, __child_l(idx)) -
			__height(me, __child_r(idx))))
		{
			/*  balance factor left node */
			int bf_r;

			bf_r = __height(me, __child_l(__child_r(idx))) -
				__height(me, __child_r(__child_r(idx)));

			if (bf_r == -1)
			{
				avltree_rotate_left(me, __child_r(idx));
			}
			else
			{
				avltree_rotate_left(me, __child_r(idx));
				avltree_rotate_right(me, __child_r(idx));
			}
		}

		if (0 == idx) break;
		idx = __parent(idx);
	}
}

static int __previous_ordered_node(avltree_t* me, int idx)
{
	int prev, i;

	for (prev = -1, i = __child_l(idx);
		/* array isn't that big, or key is null -> we don't have this child */
		i < me->size && me->nodes[i].key;
		prev = i, i = __child_r(i)
		);

	return prev;
}

void* avltree_remove(avltree_t* me, void* k)
{
	int i;

	for (i = 0; i < me->size; )
	{
		long r;
		node_t *n;

		n = &me->nodes[i];

		/* couldn't find it */
		if (!n->key)
			return NULL;

		r = me->cmp(n->key, k);

		if (r == 0)
		{
			/* replacement */
			int rep;

			me->count -= 1;

			k = n->key;

			rep = __previous_ordered_node(me, i);
			if (-1 == rep)
			{
				/* make sure the node is now blank */
				n->key = NULL;
			}
			else
			{
				/* have r's left node become right node of r's parent.
				* NOTE: r by definition shouldn't have a right child */
				__shift_up(me, __child_l(rep), __child_r(__parent(rep)));

				/* have r replace deleted node */
				__shift_up(me, rep, i);
			}

			if (i != 0)
				__rebalance(me, __parent(i));

			return k;
		}
		else if (r < 0)
		{
			i = __child_l(i);
		}
		else if (r > 0)
		{
			i = __child_r(i);
		}
		else
		{
			//assert(0);
		}
	}

	/* couldn't find it */
	return NULL;
}

void* avltree_remove1(avltree_t* me, void* k, void *v)
{
	int i;

	for (i = 0; i < me->size; )
	{
		long r;
		node_t *n;

		n = &me->nodes[i];

		/* couldn't find it */
		if (!n->key)
			return NULL;

		r = me->cmp(n->key, k);

		if (r == 0)
		{
			/* replacement */
			if (v<n->val) {
				i = __child_l(i);
				continue;
			}
			else if (v>n->val)
			{
				i = __child_r(i);
				continue;
			}

			int rep;

			me->count -= 1;

			k = n->key;

			rep = __previous_ordered_node(me, i);
			if (-1 == rep)
			{
				/* make sure the node is now blank */
				n->key = NULL;
			}
			else
			{
				/* have r's left node become right node of r's parent.
				* NOTE: r by definition shouldn't have a right child */
				__shift_up(me, __child_l(rep), __child_r(__parent(rep)));

				/* have r replace deleted node */
				__shift_up(me, rep, i);
			}

			if (i != 0)
				__rebalance(me, __parent(i));

			return k;
		}
		else if (r < 0)
		{
			i = __child_l(i);
		}
		else if (r > 0)
		{
			i = __child_r(i);
		}
		else
		{
			//assert(0);
		}
	}

	/* couldn't find it */
	return NULL;
}

void avltree_empty(avltree_t* me)
{
	int i;

	for (i = 0; i<me->size; i++)
	{
		me->nodes[i].key = NULL;
	}
}

void avltree_insert(avltree_t* me, void* k, void* v)
{
	int i;
	node_t* n;

	for (i = 0; i < me->size; )
	{
		n = &me->nodes[i];

		/* found an empty slot */
		if (!n->key)
		{
			n->key = k;
			n->val = v;
			me->count += 1;

			if (0 == i)
				return;

			__rebalance(me, __parent(i));
			return;
		}

		long r = me->cmp(n->key, k);

		if (r == 0)
		{
			if ((unsigned int)v<(unsigned int)n->val)
				i = __child_l(i);
			else
				i = __child_r(i);
			/*  we don't need to rebalance because we just overwrite this slot */

		}
		else if (r < 0)
		{
			i = __child_l(i);
		}
		else if (r > 0)
		{
			i = __child_r(i);
		}
		else
		{
			//assert(0);
		}
	}

	/* we're outside of the loop because we need to enlarge */
	//__enlarge(me);
	n = &me->nodes[i];
	n->key = k;
	n->val = v;
	me->count += 1;
}

void* avltree_iterator_peek(avltree_t * h, avltree_iterator_t * iter)
{
	if (iter->current_node < h->size)
	{
		node_t *next;

		next = &h->nodes[++iter->current_node];
		if (next->key)
			return next;
	}

	return NULL;
}

void* avltree_iterator_peek_value(avltree_t * h, avltree_iterator_t * iter)
{
	return avltree_get(h, avltree_iterator_peek(h, iter));
}

int avltree_iterator_has_next(avltree_t * h, avltree_iterator_t * iter)
{
	return NULL != avltree_iterator_peek(h, iter);
}

void *avltree_iterator_next_value(avltree_t * h, avltree_iterator_t * iter)
{
	void* k;

	k = avltree_iterator_next(h, iter);
	if (!k) return NULL;
	return avltree_get(h, k);
}

void *avltree_iterator_next(avltree_t * h, avltree_iterator_t * iter)
{
	node_t *n;
	node_t *next;

	//assert(iter);

	n = &h->nodes[iter->current_node];

	while (iter->current_node < h->size - 1)
	{
		next = &h->nodes[++iter->current_node];
		if (next->key)
			break;
	}
#if 0
	while (1)
	{
		next_id = __child_l(iter->current_node)
			next = &h->nodes[next_id];
		if (!next->key)
		{
			next_id = __child_r(iter->current_node)
				next = &h->nodes[next_id];
			if (!next->key)
			{
				int descendant;

				parent = __parent(iter->current_node);
				next_id = __parent(iter->current_node)
					while (__child_r(next_id) == parent)
					{
						parent = __parent(iter->current_node);
						next_id = __parent(iter->current_node)
							next_id = __child_r(next_id)
							next = &h->nodes[next_id];
					}

			}
		}
	}
#endif

	return n;
}

void avltree_iterator(avltree_t * h __attribute__((unused)),
	avltree_iterator_t * iter)
{
	iter->current_node = 0;
}
/* Drier program to test above function*/

static long __cmp_address(
	const void *e1,
	const void *e2
)
{
	return (unsigned long)e2 - (unsigned long)e1;
}
node_t *allocationAvlTreeNodes = 0x400000;
avltree_t allocationAvlTree;
