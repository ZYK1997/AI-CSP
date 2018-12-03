
import Data.List

judge :: Int -> Int -> [Int] -> Int -> Bool
judge maxn n state a = all f (zip [(n-1), (n-2)..1] state)
    where f (i, ai) = ai /= a && ai /= a + n - i && ai /= a - n + i

back_tracking :: Int -> Int -> [Int] -> Int
back_tracking maxn n state = if n > maxn then 1 else
    let avail = filter (judge maxn n state) [1..maxn] in 
        sum [back_tracking maxn (n + 1) (a:state) | a <- avail]

forwarding :: Int -> Int -> Int -> [[Int]] -> [[Int]]
forwarding maxn n a ass = [filter (g i) as | (i, as) <- zip [(n+1)..maxn] ass]
    where 
        g i ai = ai /= a && ai /= a + n - i && ai /= a - n + i
        f (i, as) = filter (g i) as

forward_checking :: Int -> Int -> [[Int]] -> Int
forward_checking _ _ [] = 1
forward_checking maxn n (as:ass) = 
    sum [forward_checking maxn (n+1) (forwarding maxn n a ass) | a <- as]

nQueens :: Int -> Int 
nQueens n = forward_checking n 1 $ replicate n [1..n]