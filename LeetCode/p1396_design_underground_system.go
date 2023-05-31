type RouteInfo struct {
    totalDuration int64
    count int
}

func (route *RouteInfo) AverageDuration() float64 {
    return float64(route.totalDuration) / float64(route.count)
}

type StartInfo struct {
    name string
    time int
}

type UndergroundSystem struct {
    routes map[string]map[string]*RouteInfo
    started map[int]StartInfo
}


func Constructor() UndergroundSystem {
    return UndergroundSystem {
        routes: make(map[string]map[string]*RouteInfo),
        started: make(map[int]StartInfo),
    }
}


func (this* UndergroundSystem) getRouteInfo(start, end string) *RouteInfo {
    startRoutes, startExists := this.routes[start]
    if !startExists {
        startRoutes = make(map[string]*RouteInfo)
        this.routes[start] = startRoutes
    }

    endRoute, endExists := startRoutes[end]
    if !endExists {
        endRoute = &RouteInfo {
            totalDuration: 0,
            count: 0,
        }

        startRoutes[end] = endRoute
    }

    return endRoute
}


func (this *UndergroundSystem) CheckIn(id int, stationName string, t int)  {
    this.started[id] = StartInfo {
        name: stationName,
        time: t,
    }
}


func (this *UndergroundSystem) CheckOut(id int, stationName string, t int)  {
    startInfo := this.started[id]

    duration := t - startInfo.time
    start := startInfo.name

    route := this.getRouteInfo(start, stationName)
    
    route.totalDuration += int64(duration)
    route.count++
}


func (this *UndergroundSystem) GetAverageTime(startStation string, endStation string) float64 {
    return this.getRouteInfo(startStation, endStation).AverageDuration()
}


/**
 * Your UndergroundSystem object will be instantiated and called as such:
 * obj := Constructor();
 * obj.CheckIn(id,stationName,t);
 * obj.CheckOut(id,stationName,t);
 * param_3 := obj.GetAverageTime(startStation,endStation);
 */
