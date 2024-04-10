package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	part1()
	part2()
}

func isVowel(ch rune) bool {
	return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u'
}

func part1() {
	file, err := os.Open("input.txt")
	if err != nil {
		fmt.Printf("Unable to open file: %v", err)
		panic(err)
	}
	defer file.Close()

	niceCount := 0

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		line := scanner.Text()
		vowels := 0
		hasDouble := false
		hasForbiddenDouble := false

		for idx, ch := range line {
			if isVowel(ch) {
				vowels++
			}
			if idx > 0 {
				double := line[idx-1 : idx+1]
				if double[0] == double[1] {
					hasDouble = true
				}
				if double == "ab" || double == "cd" || double == "pq" || double == "xy" {
					hasForbiddenDouble = true
				}
			}
		}

		if vowels >= 3 && hasDouble && !hasForbiddenDouble {
			niceCount++
		}
	}

	fmt.Printf("Part 1: %d\n", niceCount)

	if err = scanner.Err(); err != nil {
		fmt.Printf("Error reading from file: %v", err)
	}
}

func part2() {
	file, err := os.Open("input.txt")
	if err != nil {
		fmt.Printf("Unable to open file: %v", err)
		panic(err)
	}
	defer file.Close()

	niceCount := 0

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		line := scanner.Text()
		doubles := []string{}
		hasRecurringDouble := false
		hasIntermittentRepeat := false

		var double string
		var validDouble bool

		for idx := 1; idx < len(line); idx++ {
			double = line[idx-1 : idx+1]
			validDouble = true
			if idx > 1 {
				if double[0] == double[1] && line[idx-2] == double[0] {
                    if (idx == 2) {
                        validDouble = false
                    } else {
                        validDouble = line[idx-3:idx-1] == double
                    }
				}
				if !hasIntermittentRepeat && line[idx-1] != line[idx] && line[idx-2] == line[idx] {
					hasIntermittentRepeat = true
				}
			}
			if !hasRecurringDouble && validDouble {
				for _, d := range doubles {
					if d == double {
						hasRecurringDouble = true
						break
					}
				}
				doubles = append(doubles, double)
			}
		}

		if hasRecurringDouble && hasIntermittentRepeat {
			niceCount++
		}
	}

	fmt.Printf("Part 2: %d\n", niceCount)

	if err = scanner.Err(); err != nil {
		fmt.Printf("Error reading from file: %v", err)
	}
}
