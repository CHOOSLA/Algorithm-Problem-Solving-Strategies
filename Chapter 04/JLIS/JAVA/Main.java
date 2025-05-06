import java.util.*;
import java.io.*;

public class Main {

    public static int N, M;
    public static long[] n, m;
    public static int[][] cache;

    public static long LOWEST_LONG = Long.MIN_VALUE;

    public static int func(int aIndex, int bIndex) {
        // 기저 사례
        // 메모이 제이션이 되어있다면
        if (cache[aIndex + 1][bIndex + 1] != -1) {
            return cache[aIndex + 1][bIndex + 1];
        }

        // 옵티멀 스트럭쳐로 인해 지금이 start
        // 그럼 최소 2개의 길이를 가지게 되는 형태임
        cache[aIndex + 1][bIndex + 1] = 2;

        long a = (aIndex == -1 ? LOWEST_LONG : n[aIndex]);
        long b = (bIndex == -1 ? LOWEST_LONG : m[bIndex]);
        long max = Math.max(a, b);

        // 부분 문제화
        // a를 픽했을 경우
        for (int nextA = aIndex + 1; nextA < N; nextA++) {
            if (max < n[nextA]) { // 큰 경우 그것을 정하고 부분 문제화
                cache[aIndex + 1][bIndex + 1] = Math.max(cache[aIndex + 1][bIndex + 1], func(nextA, bIndex) + 1);
            }
        }
        // b를 픽했을 경우
        for (int nextB = bIndex + 1; nextB < M; nextB++) {
            if (max < m[nextB]) { // 큰 경우 그것을 정하고 부분 문제화
                cache[aIndex + 1][bIndex + 1] = Math.max(cache[aIndex + 1][bIndex + 1], func(aIndex, nextB) + 1);
            }
        }

        return cache[aIndex + 1][bIndex + 1];
    }

    public static void main(String[] args) throws Exception {
        System.setIn(new FileInputStream("../../../inputs/jlis.txt"));
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int cc = Integer.parseInt(br.readLine());
        for (int c = 0; c < cc; c++) {
            // 캐쉬 초기화 하기
            cache = new int[101][101];
            for (int[] arr : cache) {
                Arrays.fill(arr, -1);
            }

            // N과 M 받기기
            StringTokenizer st = new StringTokenizer(br.readLine());
            N = Integer.parseInt(st.nextToken());
            M = Integer.parseInt(st.nextToken());

            // 배열 입력받기기
            n = new long[100];
            st = new StringTokenizer(br.readLine());
            for (int i = 0; i < N; i++) {
                n[i] = Long.parseLong(st.nextToken());
            }

            m = new long[100];
            st = new StringTokenizer(br.readLine());
            for (int i = 0; i < M; i++) {
                m[i] = Long.parseLong(st.nextToken());
            }

            // 함수 실행
            System.out.println(func(-1, -1) - 2);
        }

    }

}
