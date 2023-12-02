#include <stdio.h>
#include <string.h>

char posts[100][1024];            // 100개의 글, 1024의 글자 저장.
int post_count = 0;               // 글 개수
char search_terms[100][1024];     // 검색어 저장
int search_term_count[100] = {0}; // 해당 검색어 검색 횟수
int distinct_search_terms = 0;    // 검색된 다른 검색어 수

//검색
void write_post() {
  if (post_count >= 100) {
    printf("글자 수 초과.\n");
    return;
  }

  printf("글을 작성하세요\n");
  scanf(" %[^\n]", posts[post_count]);
  post_count++;
  printf("글이 성공적으로 작성되었습니다.\n");
}

// 검색
void search_posts() {
  char search_term[1024]; // 검색어
  int exists = 0;         // 해당 검색어가 존재하는지

  printf("검색할 단어를 입력하세요: ");
  scanf("%s", search_term);

  // 개수 늘리면서 검색어가 존재하는지 확인하기
  for (int i = 0; i < distinct_search_terms; i++) {
    if (strcmp(search_terms[i], search_term) == 0) {
      search_term_count[i]++;
      exists = 1;
      break;
    }
  }
  // 없을때 새로운 검색어 추가
  if (!exists) {
    printf("검색 결과가 없습니다.\n");
    strcpy(search_terms[distinct_search_terms], search_term);
    search_term_count[distinct_search_terms]++;
    distinct_search_terms++;
  }

  // 검색 결과
  else {
    printf("검색 결과:\n");
    for (int i = 0; i < post_count; i++) {
      if (strstr(posts[i], search_term) != NULL) {
        printf("%s\n", posts[i]);
      }
    }
  }
  printf("\n");
}

// 글 삭제
void delete_posts() {
  char delete_term[1024]; // 삭제할 글
  int exists = 0;         // 해당 검색어가 존재하는지

  printf("삭제할 단어를 입력하세요: ");
  scanf("%s", delete_term);

  // 개수 늘리면서 검색어가 존재하는지 확인하기
  for (int i = 0; i < distinct_search_terms; i++) {
    if (strcmp(search_terms[i], delete_term) == 0) {
      exists = 1;
      break;
    }
  }
  // 없을 때
  if (exists) {
    printf("검색 결과가 없습니다.\n");
  }
  // 있을 때
  else {
    int cnt = 1;
    printf("목록 :\n");
    for (int i = 0; i < post_count; i++) {
      if (strstr(posts[i], delete_term) != NULL) {
        printf("%d. %s\n", cnt, posts[i]);
        cnt++;
      }
    }
    printf(">> 제할 글의 번호를 입력하세요: ");
    int idx;
    scanf("%d", &idx);
    if (idx < 1 || idx > cnt) {
      printf("잘못된 번호입니다.\n");
      return;
    }
    else {
      strcpy(posts[idx - 1], posts[post_count - 1]);
      post_count--;
      printf("글이 제거되었습니다.\n");
    }
  }
  printf("\n");
}

// 홈화면
void view_main_screen() {
  printf("관련 글 목록을 모아봅니다.\n");

  // 검색어 개수 정렬
  int temp;
  char temp_term[1024];
  for (int i = 0; i < distinct_search_terms; i++) {
    for (int j = i + 1; j < distinct_search_terms; j++) {
      if (search_term_count[i] < search_term_count[j]) {
        // Swap counts
        temp = search_term_count[i];
        search_term_count[i] = search_term_count[j];
        search_term_count[j] = temp;
        // Swap terms
        strcpy(temp_term, search_terms[i]);
        strcpy(search_terms[i], search_terms[j]);
        strcpy(search_terms[j], temp_term);
      }
    }
  }

  // 홈화면 알고리즘
  for (int i = 0; i < distinct_search_terms; i++) {
    if (search_term_count[i] > 0) {
      printf("검색어: '%s', 검색 횟수: %d\n", search_terms[i],search_term_count[i]);
      for (int j = 0; j < post_count; j++) {
        if (strstr(posts[j], search_terms[i]) != NULL) {
          printf("%s\n", posts[j]);
        }
      }
      printf("\n");
    }
  }
  printf("\n");
}

//입력
int main(void) {
  int choice;
  while (1) {
    printf("1. 글쓰기\n");
    printf("2. 검색\n");
    printf("3. 메인 화면\n");
    printf("4. 글 삭제\n");
    printf("5. 종료\n-------------\n");
    printf("입력: ");
    scanf("%d", &choice);
    switch (choice) {
    case 1:
      write_post();
      break;
    case 2:
      search_posts();
      break;
    case 3:
      view_main_screen();
      break;
    case 4:
      delete_posts();
      break;
    case 5:
      printf("프로그램을 종료합니다.\n");
      return 0;
    default:
      printf("잘못된 입력입니다.\n");
      break;
    }
  }
}
