
import Data.List
import Data.Maybe

judge :: Int -> Int -> [Int] -> Int -> Bool
judge maxn n state a = all f (zip [(n-1), (n-2)..1] state)
    where f (i, ai) = ai /= a && ai /= a + n - i && ai /= a - n + i

back_tracking :: Int -> Int -> [Int] -> Maybe [Int]
back_tracking maxn n state = if n > maxn then Just state else f g avail
    where
        f g [] = Nothing
        f g (a:as) = let ret = g a in if isNothing ret then f g as else ret
        g a = back_tracking maxn (n + 1) (a:state)
        avail = filter (judge maxn n state) [1..maxn]

forwarding :: Int -> Int -> Int -> [[Int]] -> [[Int]]
forwarding maxn n a ass = [filter (g i) as | (i, as) <- zip [(n+1)..maxn] ass]
    where 
        g i ai = ai /= a && ai /= a + n - i && ai /= a - n + i
        f (i, as) = filter (g i) as

forward_checking :: Int -> Int -> [Int] -> [[Int]] -> Maybe [Int]
forward_checking _ _ state [] = Just state
forward_checking maxn n state (as:ass) = f g as
    where
        f g [] = Nothing
        f g (a:as) = let ret = g a in if isNothing ret then f g as else ret 
        g a = forward_checking maxn (n+1) (a:state) (forwarding maxn n a ass)

nQueen :: Int -> Maybe [Int]
nQueen n = back_tracking n 1 []

nQueen2 :: Int -> Maybe [Int]
nQueen2 n = forward_checking n 1 [] $ replicate n [1..n]