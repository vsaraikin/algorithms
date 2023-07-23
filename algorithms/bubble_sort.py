def bubblesort(elements):
    swapped = False
    for n in range(len(elements), 0, -1):
        for i in range(n-1):
            if elements[i] > elements[i + 1]:
                swapped = True
                elements[i], elements[i + 1] = elements[i + 1], elements[i]       
        if not swapped:
            return
 
elements = [39, 12, 18, 85, 72, 10, 2, 18]

print(elements)
bubblesort(elements)
print(elements)
