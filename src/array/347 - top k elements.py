class Solution:
    def topKFrequent(self, nums: list[int], k: int) -> list[int]:
        freq_dict = {}

        for num in nums:
            freq_dict[num] = freq_dict.get(num, 0) + 1
        
        freq_list = [(num, freq) for num, freq in freq_dict.items()]
        freq_list.sort(key=lambda x: x[1], reverse=True)
        result = [freq_list[i][0] for i in range(k)]
        
        return result
                

s = Solution()
assert s.topKFrequent([1,1,1,2,2,3], 2) == [1, 2]
