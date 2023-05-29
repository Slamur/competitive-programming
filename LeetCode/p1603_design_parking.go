type ParkingSystem struct {
    free [3]int
}


func Constructor(big int, medium int, small int) ParkingSystem {
    return ParkingSystem {
        free: [3]int{ 
            big, 
            medium, 
            small,
        },
    }
}


func (this *ParkingSystem) AddCar(carType int) bool {
    carType--
    if this.free[carType] == 0 {
        return false
    }

    this.free[carType]--
    return true
}


/**
 * Your ParkingSystem object will be instantiated and called as such:
 * obj := Constructor(big, medium, small);
 * param_1 := obj.AddCar(carType);
 */
