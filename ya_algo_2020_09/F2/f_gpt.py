import sys
import numpy as np

# Используем большое число для представления бесконечности
INF = float('inf')

# Кэшируем результаты, чтобы не пересчитывать одно и то же
memo_check = {}

def check_column(n, mask, mask_left, mask_right):
    """
    Проверяет, выполняются ли правила для всех процессоров в колонке 'mask',
    учитывая левого соседа 'mask_left' и правого 'mask_right'.
    'None' используется для обозначения отсутствия соседа (на краях платы).
    """
    state = (n, mask, mask_left, mask_right)
    if state in memo_check:
        return memo_check[state]

    for i in range(n):
        # Определяем тип текущего процессора
        is_liar = (mask >> i) & 1

        # Собираем информацию о соседях
        neighbors = []
        # Сосед сверху
        if i > 0: neighbors.append(((mask >> (i - 1)) & 1))
        # Сосед снизу
        if i < n - 1: neighbors.append(((mask >> (i + 1)) & 1))
        # Сосед слева
        if mask_left is not None: neighbors.append(((mask_left >> i) & 1))
        # Сосед справа
        if mask_right is not None: neighbors.append(((mask_right >> i) & 1))

        if is_liar:
            # Правило для лжеца: все соседи должны быть правдивыми (0)
            if any(n == 1 for n in neighbors):
                memo_check[state] = False
                return False
        else:
            # Правило для правдивого: должен быть хотя бы один лжец (1) и один правдивый (0)
            if not (1 in neighbors and 0 in neighbors):
                memo_check[state] = False
                return False
                
    memo_check[state] = True
    return True

def solve(n, m):

    # Количество возможных масок для одной колонки
    num_masks = 1 << n
    
    # DP таблица: dp[колонка][текущая_маска][предыдущая_маска]
    # Используем только 2 слоя для колонок для экономии памяти (текущий и предыдущий)
    dp = [[[INF] * num_masks for _ in range(num_masks)] for _ in range(2)]

    # --- Инициализация для первых двух колонок ---
    for mask1 in range(num_masks):
        # Проверяем, что в первой колонке нет соседей-лжецов по вертикали
        vert_liars1 = any(((mask1 >> i) & 1) and ((mask1 >> (i + 1)) & 1) for i in range(n - 1))
        if vert_liars1:
            continue

        for mask2 in range(num_masks):
            # Проверяем вторую колонку на вертикальных лжецов
            vert_liars2 = any(((mask2 >> i) & 1) and ((mask2 >> (i + 1)) & 1) for i in range(n - 1))
            if vert_liars2:
                continue
            
            # Проверяем правила для первой колонки
            if m == 1:
                # Если всего одна колонка, у нее нет соседей слева и справа
                if check_column(n, mask1, None, None):
                    dp[0][mask1][0] = bin(mask1).count('1') # В качестве "предыдущей" маски используем 0
            elif m >= 2:
                 # Для первой колонки сосед слева - None
                if check_column(n, mask1, None, mask2):
                    liars_count = bin(mask1).count('1') + bin(mask2).count('1')
                    dp[1][mask2][mask1] = min(dp[1][mask2][mask1], liars_count)

    # --- Основной цикл DP ---
    for i in range(2, m):
        # Индексы для текущего и предыдущего слоев DP
        curr = i % 2
        prev = (i - 1) % 2
        # Очищаем текущий слой
        for j in range(num_masks):
            for k in range(num_masks):
                dp[curr][j][k] = INF

        for mask_curr in range(num_masks):
             # Проверка на вертикальных лжецов
            vert_liars_curr = any(((mask_curr >> j) & 1) and ((mask_curr >> (j + 1)) & 1) for j in range(n - 1))
            if vert_liars_curr:
                continue

            for mask_prev in range(num_masks):
                for mask_prev_prev in range(num_masks):
                    if dp[prev][mask_prev][mask_prev_prev] == INF:
                        continue
                    
                    # Проверяем валидность тройки колонок для центральной (mask_prev)
                    if check_column(n, mask_prev, mask_prev_prev, mask_curr):
                        new_liars = dp[prev][mask_prev][mask_prev_prev] + bin(mask_curr).count('1')
                        dp[curr][mask_curr][mask_prev] = min(dp[curr][mask_curr][mask_prev], new_liars)

    # --- Поиск результата ---
    min_liars = INF
    if m == 1:
        # Для m=1 результат уже в dp[0]
        for mask in range(num_masks):
            if dp[0][mask][0] != INF:
                min_liars = min(min_liars, dp[0][mask][0])
    else:
        # Для m > 1 проверяем последнюю колонку
        last_col_idx = (m - 1) % 2
        for mask_last in range(num_masks):
            for mask_penultimate in range(num_masks):
                if dp[last_col_idx][mask_last][mask_penultimate] != INF:
                    # Проверяем правила для последней колонки (справа соседа нет)
                    if check_column(n, mask_last, mask_penultimate, None):
                        min_liars = min(min_liars, dp[last_col_idx][mask_last][mask_penultimate])

    # print(min_liars if min_liars != INF else "Решение не найдено")
    return min_liars if min_liars != INF else m*n

# Чтобы запустить код, раскомментируйте строку ниже и введите n и m
# например: 4 4
# solve()

# solve(6, 6)

def test1() :
    assert(solve(1, 1) == 1);
    assert(solve(1, 2) == 2);
    assert(solve(1, 3) == 3);
    assert(solve(1, 4) == 2);
    assert(solve(1, 5) == 5);
    assert(solve(1, 7) == 3);
    assert(solve(2, 1) == 2);
    assert(solve(3, 1) == 3);
    assert(solve(4, 1) == 2);
    assert(solve(5, 1) == 5);
    assert(solve(7, 1) == 3);

    assert(solve(1, 100) == 34);


def test2() :
    assert(solve(2, 2) == 4);
    assert(solve(2, 3) == 2);
    assert(solve(2, 4) == 8);
    assert(solve(2, 5) == 3);
    assert(solve(2, 6) == 4);
    assert(solve(2, 7) == 4);
    assert(solve(2, 8) == 5);
    assert(solve(2, 11) == 6);
    assert(solve(2, 12) == 7);
    assert(solve(2, 10) == 6);
    assert(solve(2, 100) == 51);


def test3() :
    assert(solve(3, 3) == 3);
    assert(solve(3, 4) == 4);
    assert(solve(3, 5) == 4);
    assert(solve(3, 6) == 6);
    assert(solve(3, 7) == 6);
    assert(solve(3, 9) == 7);
    assert(solve(3, 10) == 9);
    assert(solve(3, 15) == 12);
    assert(solve(3, 16) == 13);


def test4() :
    assert(solve(4, 4) == 4);
    assert(solve(4, 5) == 6);
    assert(solve(4, 6) == 7);
    assert(solve(4, 7) == 7);
    assert(solve(4, 8) == 8);
    assert(solve(4, 9) == 10);
    # assert(solve(4, 10) == 11);


def test5() :
    assert(solve(5, 5) == 7);
    # assert(solve(5, 6) == 9);
    assert(solve(5, 7) == 10);
    assert(solve(5, 8) == 11);


def test6() :
    assert(solve(6, 6) == 10);
    assert(solve(6, 7) == 11);
    # assert(solve(6, 8) == 13);
    assert(solve(6, 9) == 14);
    assert(solve(6, 10) == 16);


def test7() :
    assert(solve(7, 7) == 12);
    assert(solve(7, 8) == 14);
    assert(solve(7, 12) == 7*3);


def testAll() :
    test1()
    test2()
    test3()
    test4()
    test5()
    test6()
    test7()

def fillArray() :
    t = [ [0]*101 for i in range(8)]
    for n in range(1, 8):
        for m in range(1, 101):
            t[n][m] = solve(n, m)
    print(np.matrix(t))


# testAll()
# solve(7, 100)
fillArray()
