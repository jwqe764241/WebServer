## 웹서버

간단한 파일전송만 구현

##### 프로젝트 구조

```
├── bin
│   └── ......
├── doc
│   └── ......
├── include
│   └── ......
├── lib
│   └── ......
├── obj
│   └── ......
├── src
│   └── ......
├── test
│   └── ......
└────────────────
```

##### 로컬에 생성되는 폴더
- bin : 기본 출력파일 경로
- obj : 기본 중간파일 경로

##### 그 외
- doc : 문서 파일들이 담길 경로
- include : 헤더파일 경로
- lib : 외부 라이브러리파일 경로
- src : 소스파일 경로
- test : 테스트소스, 테스트 프로젝트 경로 (기본 .gitignore에 등록되어있음, 전부가 참고할 테스트코드들은 add -f로 추가됨)
