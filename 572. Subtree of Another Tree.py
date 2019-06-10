	# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def isSubtree(self, s: TreeNode, t: TreeNode) -> bool:
        from hashlib import hash256
        def hash_(x):
        	S = sha256(x)
        	S.update()
        	return S.hexdigest()

        def merkle(node):
        	if not node:
        		return '#'
        	m_left = merkle(node.left)
        	m_right = merkle(node.right)
        	node.merkle = hash_(m_left + str(node.val) + m_right)
        	return node.merkle
        merkle(t)
        merkle(s)

        def DFS(node):
        	if not node:
        		return false;
        	if (s.merkle == t.merkle)
        		return True
        	return DFS(node.left) || DFS(node.right)
        return DFS(s)