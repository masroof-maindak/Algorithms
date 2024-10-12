package main

import "fmt"

func iter(a, b int) int {
	ret := 0
	for b != 0 {

		res := a
		pow2 := 1

		for pow2+pow2 <= b {
			res += res
			pow2 += pow2
		}

		ret += res
		b -= pow2

	}

	return ret
}

func rec(a,  b int) int {
	if b == 0 {
		return 0
	}

	res := a
	pow2 := 1

	for pow2+pow2 <= b {
		res += res
		pow2 += pow2
	}

	return res + (rec(a, b-pow2))
}

func main() {
	fmt.Println(iter(5, 100))
	fmt.Println(rec(6, 101))
}
