package main

import "fmt"

func fastMultIter(a int, b int) int {
	ret := 0
	for b != 0 {

		partial := a
		pwrOf2 := 1

		for pwrOf2+pwrOf2 <= b {
			partial += partial
			pwrOf2 += pwrOf2
		}

		ret += partial
		b -= pwrOf2

	}

	return ret
}

func fastMultRec(a int, b int) int {
	if b == 0 {
		return 0
	}

	partial := a
	pwrOf2 := 1

	for pwrOf2+pwrOf2 <= b {
		partial += partial
		pwrOf2 += pwrOf2
	}

	return partial + (fastMultRec(a, b-pwrOf2))
}

func main() {
	fmt.Println(fastMultIter(5, 100))
	fmt.Println(fastMultRec(6, 101))
}
