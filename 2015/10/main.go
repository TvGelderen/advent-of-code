package main

import (
	"fmt"
	"strconv"
)

func main() {
	nums := []string{"1321131112"}
	times := 50

	for iteration := 0; iteration < times; iteration++ {
        fmt.Printf("Iteration: %d\n", iteration)

		rangeNums := nums
		for idx, num := range rangeNums {
			result := ""
			currentNum := rune(num[0])
			currentNumCount := 0

			for _, ch := range num {
				if ch == currentNum {
					currentNumCount++
				} else {
					result += strconv.Itoa(currentNumCount) + string(currentNum)
					currentNum = ch
					currentNumCount = 1
				}
			}

			result += strconv.Itoa(currentNumCount) + string(currentNum)
            nums[idx] = result
		}
	}

	count := 0
	for _, num := range nums {
		count += len(num)
	}

	fmt.Printf("Length: %d\n", count)
}

func toInt(r byte) int {
    return int(r - '0')
}
