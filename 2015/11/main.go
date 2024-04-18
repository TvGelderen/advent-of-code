package main

import (
	"fmt"
	"strings"
)

func main() {
	password := "cqjxxzaa"

	for !isValid(password) {
		updateIdx := len(password) - 1
        for updateIdx != -1 {
            if password[updateIdx] == 'z' {
                password = password[:updateIdx] + "a" + password[updateIdx+1:]
                if updateIdx == 0 {
                    password = "a" + password
                }
                updateIdx--
            } else {
                if isForbiddenChar(password[updateIdx] + 1) {
                    a := strings.Repeat("a", len(password) - 1 - updateIdx)
                    password = fmt.Sprintf("%s%c%s", password[:updateIdx], password[updateIdx]+2, a)
                    break
                }
                password = fmt.Sprintf("%s%c%s", password[:updateIdx], password[updateIdx]+1, password[updateIdx+1:])
                break
            }
        }
	}

    fmt.Printf("Part 1: %s\n", password)
}

func isValid(password string) bool {
	var doubleChar byte
	hasDouble := false
	hasTwoDoubles := false
    hasIncreasingStraight := false

	for idx := range password {
		if isForbiddenChar(password[idx]) {
			return false
		}
		if idx+2 < len(password) &&
			password[idx] == password[idx+1]-1 &&
			password[idx+1] == password[idx+2]-1 {
            hasIncreasingStraight = true
		}
		if !hasTwoDoubles &&
			idx+1 < len(password) &&
			password[idx] == password[idx+1] {
			if !hasDouble {
				hasDouble = true
				doubleChar = password[idx]
				continue
			}

			if password[idx] != doubleChar {
				hasTwoDoubles = true
			}
		}
	}
    return hasIncreasingStraight && hasTwoDoubles
}

func isForbiddenChar(ch byte) bool {
	return ch == 'i' || ch == 'o' || ch == 'l'
}
