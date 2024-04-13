package main

import (
	"bufio"
	"errors"
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"
)

func main() {
	file, err := os.Open("input.txt")
	if err != nil {
		fmt.Printf("Unable to open file: %v", err)
		panic(err)
	}

	circuit := make(map[string]uint16)
	var backlog []string

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		err = processLine(scanner.Text(), circuit)
		if err != nil {
			backlog = append(backlog, scanner.Text())
		}
	}

	for len(backlog) > 0 {
		currentBacklog := backlog
		backlog = nil

		for _, line := range currentBacklog {
			err = processLine(line, circuit)
			if err != nil {
				backlog = append(backlog, line)
			}
		}
	}

	var strengthA uint16
	for wire, strength := range circuit {
		if wire == "a" {
			strengthA = strength
			break
		}
	}

	fmt.Printf("Part 1: %d\n", strengthA)

	circuit = make(map[string]uint16)
	circuit["b"] = strengthA
	backlog = make([]string, 0)

	file, _ = os.Open("input.txt")
	scanner = bufio.NewScanner(file)
	for scanner.Scan() {
		err = processLine(scanner.Text(), circuit)
		if err != nil {
			backlog = append(backlog, scanner.Text())
		}
	}

	for len(backlog) > 0 {
		currentBacklog := backlog
		backlog = nil

		for _, line := range currentBacklog {
			err = processLine(line, circuit)
			if err != nil {
				backlog = append(backlog, line)
			}
		}
	}

	for wire, strength := range circuit {
		if wire == "a" {
			strengthA = strength
			break
		}
	}

	fmt.Printf("Part 2: %d\n", strengthA)

	if err := scanner.Err(); err != nil {
		fmt.Printf("Error reading from file: %v\n", err)
	}
}

func processLine(line string, circuit map[string]uint16) error {
	splitLine := strings.Split(line, " -> ")
	lhs := strings.Split(splitLine[0], " ")
	wire := splitLine[1]

	switch len(lhs) {
	case 1:
        if _, ok := circuit[wire]; ok {
            return nil
        }
		strength, err := strconv.ParseInt(lhs[0], 10, 16)
		if err != nil {
			if val, ok := circuit[lhs[0]]; ok {
				circuit[wire] = val
			} else {
				return errors.New("Input without known signal strength")
			}
		} else {
			circuit[wire] = uint16(strength)
		}
	case 2:
		val, ok := circuit[lhs[1]]
		if !ok {
			return errors.New("Input without known signal strength")
		}
		circuit[wire] = ^val
	case 3:
		switch lhs[1] {
		case "OR", "AND":
			val1, ok := circuit[lhs[0]]
			if !ok {
				if val, err := strconv.ParseInt(lhs[0], 10, 16); err != nil {
					return errors.New("Input without known signal strength")
				} else {
					val1 = uint16(val)
				}
			}
			val2, ok := circuit[lhs[2]]
			if !ok {
				return errors.New("Input without known signal strength")
			}
			if lhs[1] == "OR" {
				circuit[wire] = val1 | val2
			} else {
				circuit[wire] = val1 & val2
			}
		case "LSHIFT", "RSHIFT":
			val, ok := circuit[lhs[0]]
			if !ok {
				return errors.New("Input without known signal strength")
			}
			n, err := strconv.ParseInt(lhs[2], 10, 16)
			if err != nil {
				log.Fatal("Error parsing left or right shift number")
			}
			if lhs[1] == "LSHIFT" {
				circuit[wire] = val << n
			} else {
				circuit[wire] = val >> n
			}
		}
	}

	return nil
}
