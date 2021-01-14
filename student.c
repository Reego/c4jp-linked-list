#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "student.h"

static const double HONOUR_ROLL_MIN_GPA = 3.50;

int compare_by_gpa(struct ll_node *a, struct ll_node *b) {
    double diff = LL_ENTRY(a, struct student, node)->gpa - LL_ENTRY(b, struct student, node)->gpa;
    if (diff > 0.0) {
        return 1;
    }
    else if (diff < 0.0) {
        return -1;
    }
    return 0;
}

struct student *student_worst_performer(struct student *list) {
    assert(list != NULL);
    
    struct ll_node *min_node = ll_min(&list->node, compare_by_gpa);
    return LL_ENTRY(min_node, struct student, node);
}

struct student *student_valedictorian(struct student *list) {
    assert(list != NULL);

    struct ll_node *max_node = ll_max(&list->node, compare_by_gpa);
    return LL_ENTRY(max_node, struct student, node);
}

bool honour_roll_filter(struct ll_node *node) {
    return LL_ENTRY(node, struct student, node)->gpa >= HONOUR_ROLL_MIN_GPA;
}

struct student *student_honour_roll(struct student *list) {
    assert(list != NULL);
    
    struct ll_node *filtered = ll_filter(&list->node, honour_roll_filter);

    if (filtered != NULL) {
        return LL_ENTRY(filtered, struct student, node);
    }
    return NULL;
}
