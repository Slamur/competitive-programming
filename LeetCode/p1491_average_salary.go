func average(salary []int) float64 {
    n := len(salary)

    minSalary, maxSalary := 1000 * 1000 * 1000, 0
    for i := 0; i + 1 < n; i += 2 {
        smallSalary, largeSalary := salary[i], salary[i + 1]
        if smallSalary > largeSalary {
            smallSalary, largeSalary = largeSalary, smallSalary
        }
        if minSalary > smallSalary {
            minSalary = smallSalary
        }
        if maxSalary < largeSalary {
            maxSalary = largeSalary
        }
    }

    if n % 2 == 1 {
        lastSalary := salary[n - 1]
        if minSalary > lastSalary {
            minSalary = lastSalary
        }
        if maxSalary < lastSalary {
            maxSalary = lastSalary
        }
    }

    sum := 0
    for _, value := range salary {
        sum += value
    }

    sum -= minSalary
    sum -= maxSalary

    return float64(sum) / float64(n - 2)
}
