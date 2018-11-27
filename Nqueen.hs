

N :: Int
N = 8

type State = [Int]

check :: State -> Int -> Int -> Bool
check s n a = filter (==a) s == []
			&& filter (\(i, x) -> a + n - i == x) (zip [1..] s) == []
			&& filter (\(i, x) -> a - n + i == x) (zip [1..] s) == []

avail :: State -> Int -> [Int]
avail s n = filter (check s n) [1..N]