# MathEngine
직접 만든 수학 엔진입니다.

## features 
- Constans: 상수 정의

- MathUtils: 자주 사용되는 수학 함수 정의

- Vector2: 2차원 벡터
- Matrix2x2: 2x2 행렬

## Dependency
- cmath
  - MathUtils
  
- Constans
  - MathUtils

- MathUtils
  - Vector2
  - Matrix2x2

- Vector
  - Matrix2x2

## Journal
프로젝트를 진행하면서 기타 느낀 것

### 표준 라이브러리와 이름이 겹치는 일이 없도록 하자 
`Math.h` 로 파일을 만들었다가  `<math.h>` 라이브러리와 이름이 중복되는 바람에 의도치 않는 오류를 겪었다.
_2023-07-30_
