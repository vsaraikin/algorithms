class TimeMap:

    def __init__(self):
        self.storage = {}

    def set(self, key: str, value: str, timestamp: int) -> None:
        if not self.storage.get(key, []):
            self.storage[key] = []
        self.storage[key].append((value, timestamp))
        

    def get(self, key: str, timestamp: int) -> str:
        res = ''
        data = self.storage.get(key)
        left, right = 0, len(data) - 1
        while left <= right:
            mid = (left + right) // 2
            if data[mid][1] <= timestamp:
                res = data[mid][0]
                left = mid + 1
            else:
                right = mid - 1
        return res


timeMap = TimeMap()
timeMap.set("foo", "bar", 1)
timeMap.get("foo", 1);      
timeMap.get("foo", 3);      
timeMap.set("foo", "bar2", 4)
timeMap.get("foo", 4);      
timeMap.get("foo", 5);      