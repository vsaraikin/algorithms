# https://www.hackerearth.com/practice/algorithms/sorting/merge-sort/visualize/
# https://opendsa-server.cs.vt.edu/embed/mergesortAV
# https://visualgo.net/en/sorting

def merge_sort(lst):
    if len(lst) <= 1:  # base case
        return lst

    # divide array in half and merge sort recursively
    half = len(lst) // 2
    left_half = merge_sort(lst[:half])
    right_half = merge_sort(lst[half:])

    return merge(left_half, right_half)


def merge(left, right):
    merged = []
    left_index = 0
    right_index = 0

    # move through the lists until we have exhausted one
    while left_index < len(left) and right_index < len(right):
        if left[left_index] <= right[right_index]:
            merged.append(left[left_index])
            left_index += 1
        else:
            merged.append(right[right_index])
            right_index += 1

    # append any leftovers. Because we've exhausted one list, we know 
    # everything in the other list is larger
    while left_index < len(left):
        merged.append(left[left_index])
        left_index += 1

    while right_index < len(right):
        merged.append(right[right_index])
        right_index += 1
    
    # if left < right:
    #     merged.append(left)
    #     merged.append(right)
    # else:
    #     merged.append(right)
    #     merged.append(left)

    return merged


# test the function
lst = [5, 3, 2, 7, 1, 0, 4, 6]
print(merge_sort(lst))
