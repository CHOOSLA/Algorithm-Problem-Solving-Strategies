import java.util.*;
import java.io.*;

class Main {
    public static String W, S;
    public static int[][] cache;
    public static ArrayList<String> result;

    public static int check(int wIdx, int sIdx) {
        // 기저 사례
        // 1. cache에 저장되어 있는 경우
        // 2. 끝났거나 범위 밖인 경우

        // 1. 번 부분
        if (cache[wIdx][sIdx] != -1)
            return cache[wIdx][sIdx];

        // *가 나오기 전까지 끝까지 돌리게 된다.
        while (wIdx < W.length() && sIdx < S.length()
                && (W.charAt(wIdx) == '?' || W.charAt(wIdx) == S.charAt(sIdx))) {
            ++wIdx;
            ++sIdx;
        }

        // 2. 둘 다 끝가지 가게 된 경우 == 성공
        if (wIdx == W.length()) {
            cache[wIdx][sIdx] = (sIdx == S.length() ? 1 : 0);
            return cache[wIdx][sIdx];
        }

        // * 을 만났을 경우
        if (W.charAt(wIdx) == '*') {
            // 완전 탐색으로 보내서 작은 문제에서 풀게 된다.
            for (int skip = 0; skip + sIdx <= S.length(); skip++) {
                // 완벽하게 매칭이 되었을 경우 return 1;
                if (check(wIdx + 1, sIdx + skip) == 1) {
                    cache[wIdx][sIdx] = 1;
                    return 1;
                }
            }
        }

        // false 인 경우 처리
        cache[wIdx][sIdx] = 0;
        return cache[wIdx][sIdx];
    }

    public static void main(String[] args) throws Exception {
        System.setIn(new FileInputStream("../../../inputs/wildcard.txt"));
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        // result 초기화
        result = new ArrayList<>();

        // 입력 받기 및 실행행
        int C = Integer.parseInt(br.readLine());
        for (int i = 0; i < C; i++) {
            W = br.readLine();
            int N = Integer.parseInt(br.readLine());
            for (int j = 0; j < N; j++) {
                // cache 초기화
                cache = new int[101][101];
                for (int[] arr : cache) {
                    Arrays.fill(arr, -1);
                }
                S = br.readLine();
                if (check(0, 0) == 1) {
                    result.add(new String(S));
                }
            }
        }

        Collections.sort(result);

        for (String r : result) {
            System.out.println(r);
        }
    }
}