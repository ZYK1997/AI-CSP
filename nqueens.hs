
import Data.List

-- judge :: Int -> Int -> [Int] -> Int -> Bool
-- judge maxn n state a = all f (zip [(n-1), (n-2)..1] state)
--     where f (i, ai) = ai /= a && ai /= a + n - i && ai /= a - n + i

-- backTracking :: Int -> Int -> [Int] -> Int
-- backTracking maxn n state = if n > maxn then 1 else
--     let avail = filter (judge maxn n state) [1..maxn] in 
--         sum [backTracking maxn (n + 1) (a:state) | a <- avail]

backTracking 0 state _ = [state]
backTracking n state as = 
    foldl' (++) [] [backTracking (n-1) (a:state) (delete a as) | a <- as, judge state a] where
        judge state a = and [a /= c + i && a /= c - i | (i, c) <- zip [1..] state]

queens n = backTracking n [] [1..n]


forwardChecking state [] = [state]
forwardChecking state (as:ass) = 
    foldl' (++) [] [forwardChecking (a:state) (forwarding a ass) | a <- as] where
        forwarding a ass = [filter (\c -> (c /= a) && (c /= a + i) && (c /= a - i)) as | (i, as) <- zip [1..] ass]

nQueens n = forwardChecking [] $ replicate n [1..n]