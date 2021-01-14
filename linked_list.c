#include <stdlib.h>
#include <assert.h>
#include "linked_list.h"

void ll_init(struct ll_node *node) {
    assert(node != NULL);
    node->prev = NULL;
    node->next = NULL;
}

bool ll_has_next(struct ll_node *node) {
    assert(node != NULL);
    return node->next != NULL;
}

bool ll_has_prev(struct ll_node *node) {
    assert(node != NULL);
    return node->prev != NULL;
}

struct ll_node *ll_next(struct ll_node *node) {
    assert(node != NULL);
    return node->next;
}

struct ll_node *ll_prev(struct ll_node *node) {
    assert(node != NULL);
    return node->prev;
}

size_t ll_size(struct ll_node *head) {
    assert(head != NULL);

    struct ll_node *node = head;

    size_t size = 1;
    while ((node = node->next) != NULL) {
        size++;
    }
    
    return size;
}

struct ll_node *ll_head(struct ll_node *list) {
    assert(list != NULL);
    
    struct ll_node *node = list;
    while (node->prev != NULL) {
        node = node->prev;
    }
    
    return node;
}

struct ll_node *ll_tail(struct ll_node *list) {
    assert(list != NULL);
    
    struct ll_node *node = list;
    while (node->next != NULL) {
        node = node->next;
    }
    
    return node;
}

struct ll_node *ll_get(struct ll_node *node, size_t index) {
    assert(node != NULL);
    
    size_t cur_index = 0;
    while (cur_index < index && (node = node->next) != NULL) {
        cur_index++;
    }

    if (cur_index == index) {
        return node;
    }
    return NULL;
}

void ll_insert_before(struct ll_node *new, struct ll_node *existing) {
    assert(new != NULL);
    assert(existing != NULL);

    struct ll_node *old_prev = existing->prev;
    
    new->prev = old_prev;
    if (old_prev != NULL) {
        old_prev->next = new;
    }

    new->next = existing;
    existing->prev = new;
}

void ll_insert_after(struct ll_node *new, struct ll_node *existing) {
    assert(new != NULL);
    assert(existing != NULL);
    
    struct ll_node *old_next = existing->next;
    
    new->next = old_next;
    if (old_next != NULL) {
        old_next->prev = new;
    }

    new->prev = existing;
    existing->next = new;
}

void ll_insert_first(struct ll_node *new, struct ll_node *list) {
    assert(new != NULL);
    assert(list != NULL);
   
    struct ll_node *head = ll_head(list);
    ll_insert_before(new, head);
}

void ll_insert_last(struct ll_node *new, struct ll_node *list) {
    assert(new != NULL);
    assert(list != NULL);

    struct ll_node *tail = ll_tail(list);
    ll_insert_after(new, tail);
}

void ll_remove(struct ll_node *node) {
    assert(node != NULL);
    
    struct ll_node *prev_node = node->prev;
    struct ll_node *next_node = node->next;

    if (prev_node != NULL) {
        prev_node->next = next_node;
    }
    if (next_node != NULL) {
        next_node->prev = prev_node;
    }
}

struct ll_node *ll_min(struct ll_node *list, ll_comparator_t comparator) {
    assert(list != NULL);
    assert(comparator != NULL);
    
    struct ll_node *min = list;

    struct ll_node *node = list->next;
    while (node != NULL) {
        if (comparator(node, min) < 0) {
            min = node;
        }
        node = node->next;
    }

    return min;
}

struct ll_node *ll_max(struct ll_node *list, ll_comparator_t comparator) {
    assert(list != NULL);
    assert(comparator != NULL);

    struct ll_node *max = list;

    struct ll_node *node = list->next;
    while (node != NULL) {
        if (comparator(node, max) > 0) {
            max = node;
        }
        node = node->next;
    }

    return max;
}

struct ll_node *ll_filter(struct ll_node *list, ll_predicate_t predicate) {
    assert(list != NULL);
    assert(predicate != NULL);

    struct ll_node *first_filtered = NULL;
    struct ll_node *node = list;
    
    do {
        if (predicate(node)) {
            if (first_filtered == NULL) {
                first_filtered = node;
            }
        }
        else {
            ll_remove(node);
        }
        node = node->next;
    }
    while (node != NULL);

    if (first_filtered != NULL) {
        return ll_head(first_filtered);
    }
    return NULL;
}
