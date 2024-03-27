package main
import "fmt"

func triSum (n int) int {
    if n == 0 || n == 1 {
        return 0
    } else if n == 2 {
        return 1
    }

    return triSum(n-1) + triSum(n-2) + triSum(n-3)
}

func fiboBad (n int) int {
    if n < 2 {
        return n;
    }

    return fiboBad(n-1) + fiboBad(n-2);
}

func fiboRecursive (n int, cache map[int]int) int {
    if n < 2 {
        return n
    }

    // check if in bounds and determined already. Return if found.
    if ans, ok := cache[n]; ok {
        return ans
    }

    answer := fiboRecursive(n-1, cache) + fiboRecursive(n-2, cache)
    cache[n] = answer
    return answer
}

func fiboWrapper (n int) int {
    cache := make(map[int]int)
    return fiboRecursive(n, cache)
}

func pwr(num int, exp int) int {
    if exp == 1 {
        return num;
    }

    if exp % 2 == 0 {
        expN := exp/2
        return pwr(num, expN) * pwr(num, expN)
    } else {
        expN := (exp-1)/2
        return num * pwr(num, expN) * pwr(num, expN)
    }
}

func main() {
    n := 11
    num := 2
    exp := 6
    fmt.Println("Trisum of", n, "=", triSum(n))
    fmt.Println("Recursive fibonacci of", n, "=", fiboBad(n))
    fmt.Println("Memoized recursive fibonacci of", n, "=", fiboWrapper(n))
    fmt.Println("Fast multiplication of", num, "^", exp, "=", pwr(num,exp))
}
