#ifndef MERGESORT_H
#define MERGESORT_H

#include "Medicine.h"
#include <vector>

void merge(std::vector<Medicine>& arr, int left, int mid, int right);
void mergeSort(std::vector<Medicine>& arr, int left, int right);

#endif
