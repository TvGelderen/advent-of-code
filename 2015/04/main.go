package main

import (
	"crypto/md5"
	"encoding/hex"
	"fmt"
)

func main() {
    number := 0
    
    for true {
        hash := md5.Sum([]byte(fmt.Sprintf("ckczppom%d", number)))
        hexString := hex.EncodeToString(hash[:])

        if hexString[:5] == "00000" {
            break
        }

        number++ 
    }

    fmt.Printf("Part 1: %d\n", number)

    for true {
        hash := md5.Sum([]byte(fmt.Sprintf("ckczppom%d", number)))
        hexString := hex.EncodeToString(hash[:])

        if hexString[:6] == "000000" {
            break
        }

        number++ 
    }

    fmt.Printf("Part 2: %d\n", number)
}
