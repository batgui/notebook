class Solution:
    def findMaximizedCapital(self, k: int, W: int, Profits: List[int], Capital: List[int]) -> int:
        heap = []
        project = sorted(zip(Capital, Profits))
        i = 0
        while(k):
        	while(i < len(project) and project[i][0] <= W):
        		heapq.heappush(heap, -project[i][1])
        		i += 1
        	if heap:
        		W -= heapq.heappop(heap)
        	k = k - 1
        return W