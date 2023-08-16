package main

import (
	"fmt"
)

func maxArea(height []int) int {

	maximum := 0
	n := len(height)
	v := 0
	i := 0
	j := n - 1
	volume := 0

	for {
		if i >= n && j <= i {
			return int(maximum)
		}

		if height[i] > height[j] {
			v = height[j]
			volume = v * (j - i)
			j -= 1
		} else {
			v = height[i]
			volume = v * (j - i)
			i += 1
		}
		if volume > maximum {
			maximum = volume
		}

	}

}

func main() {
	pool := []int{1, 8, 6, 2, 5, 4, 8, 3, 7}
	res := maxArea(pool)
	fmt.Println(res)
}
