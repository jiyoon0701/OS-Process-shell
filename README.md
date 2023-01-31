# Make Unix Shell

## 상세 내용
<b> 1. 명령 입력 후 입력한 명령을 실행하는 하위 프로세스 생성 후 추가 명령어 대기 </b> <br> <br>
<b> 2.기본 쉘, 경로, 내장 명령, 리디렉션, 병령 명려으 프로그램 오류 구현 </b>

## 요구사항 요약
<img width="900" alt="image" src="https://user-images.githubusercontent.com/83527046/215843801-5f0fb4c1-990f-4e0f-9336-f4891a9ff56d.png">
  
# 프로젝트 내용

## 대화형 프롬프트 출력하는 기본 쉘 구현 - 사용자와의 상호작용 <br>
> <b> 1. 주어진 인수와 함께 프로그램이 정상적으로 실행되는가? </b> <br>
 <img width="579" alt="image" src="https://user-images.githubusercontent.com/83527046/215845737-f84d0137-3b73-4d9b-becd-558ec48f99c2.png">
 
> <b> 2. 실향할 명령을 알리기 위해 반복적으로 입력을 요청 받는가?</b> <br>
 <img width="472" alt="image" src="https://user-images.githubusercontent.com/83527046/215846129-7be664c8-9fd8-4489-8a05-2cfb24c794c4.png">
 
> <b> 3. 사용자가 내장 명령 exit를 입력할 때 까지 반복적으로 입력 요청을 받는가?</b> <br>
 <img width="389" alt="image" src="https://user-images.githubusercontent.com/83527046/215846312-288758d3-608e-4106-ad60-095ef22e4b1c.png">
 
> <b> 4. 사용자가 한 번에 하나씩 명령을 입력하면 그에 따라 명령이 하나씩 실행되는 대화형 모드로 실행되는가? </b><br>
  <img width="456" alt="image" src="https://user-images.githubusercontent.com/83527046/215846449-8e693f8b-5312-4a52-9cba-632224f136ee.png">
  
> <b> 5. 사용자가 명령어, 인수 및 다양한 연산자 앞 뒤에 많은 양의 공백을 넣어도 정상적으로 작동하는가?</b> <br>
 <img width="593" alt="image" src="https://user-images.githubusercontent.com/83527046/215847657-945b350d-443a-4753-a5ab-e7f3006075b0.png">
 
 <br>
 
## 쉘 지정 디렉터리 경로 구현 - 배치모드

> <b> 1. 명령어의 입력 파일이 제공되는 배치모드를 지원하는가? </b> <br>
  <img width="327" alt="image" src="https://user-images.githubusercontent.com/83527046/215847831-21bee93e-fca8-4f09-9550-7adc8e6f157b.png">
  
> <b> 2. 배치 파일이 정상적으로 열리는가? </b> <br>

  <img width="326" alt="image" src="https://user-images.githubusercontent.com/83527046/215848032-44a527d3-c7be-4384-85e3-195db787273a.png"><img width="263" alt="image" src="https://user-images.githubusercontent.com/83527046/215848068-7d4d416d-0dcd-4445-98b9-9d73fef262a5.png">

> <b> 3. 배치모드에서 명령어를 사용자 입력이 아닌 파일에서 읽어오는가? </b> <br>
 <img width="327" alt="image" src="https://user-images.githubusercontent.com/83527046/215848427-c4b91cf7-bb30-41de-9e45-c7b7df832d8d.png">

<br>

## 내장 명령 구현

> <b> 1. cd명령을 통해 작업 디렉토리를 정상적으로 변경할 수 있는가? </b> <br>
<img width="468" alt="image" src="https://user-images.githubusercontent.com/83527046/215848609-3fb4cb3c-4e9d-4f20-b458-91b5e5062727.png">

> <b> 2. path 명령을 실행할 경우 이전 경로를 새로운 경로로 정상적으로 덮어 쓰는가? </b> <br>
 <img width="394" alt="image" src="https://user-images.githubusercontent.com/83527046/215848858-c2225cda-12de-465a-96d7-a2a09b1f4be2.png">

> <b> 3. path 명령 사용자가 경로를 비우면 쉘은 어떤 프로그램도 실행할 수 없어야 함 </b> <br>
 <img width="437" alt="image" src="https://user-images.githubusercontent.com/83527046/215849010-f0e00440-b5ca-4742-b7bc-b27a6c742d99.png">
 
> <b> 4. exit 명령을 실행할 경우 어떤 모드에서든 정상적으로 종료가 되는가? </b><br>
 <img width="508" alt="image" src="https://user-images.githubusercontent.com/83527046/215849156-19720b9e-6260-4fc6-b111-e0141cc5238f.png">
 
 <br>
 
## 입력을 파일에 쓰는 리디렉션 구현

> <b> 1. 리디렉션으로 출력할 경우 키보드로부터 입력 받은 내용이 파일로 저장이 되는가? </b> <br>
 <img width="388" alt="image" src="https://user-images.githubusercontent.com/83527046/215849400-d3a23b28-ef71-496c-b2f9-5f4b50a1e401.png">

> <b> 2. 리다이렉션으로 출력(>)사용할 경우 기존 파일이 있을 때, 기존 파일을 덮어쓰고 저장하는가? </b> <br>

 <img width="228" alt="image" src="https://user-images.githubusercontent.com/83527046/215849495-3e8f0a2f-c9a2-48a3-bace-f6c8743638ad.png"> <img width="256" alt="image" src="https://user-images.githubusercontent.com/83527046/215849513-271e8bae-358f-4400-bec0-07806abee957.png">

> <b> 3. 리다이렉션으로 출력(>>)사용할 경우 같은 이름의 기존 파일이 있을 경우 그 파일에 이어서 내용이 추가 저장되는가? </b> <br>
 <img width="474" alt="image" src="https://user-images.githubusercontent.com/83527046/215849773-250e5167-87a8-4617-8cc6-9da28eafe31a.png">
 
 <br>
 
## 병렬 명령 구현

> <b> 1. 명령어를 병렬로 실행시킬 수 있는가? </b> <br>
 <img width="380" alt="image" src="https://user-images.githubusercontent.com/83527046/215849897-c414622f-d4b2-4c1f-b109-ca7683787d25.png">

> <b> 2. 입력 순서대로 명령이 실행 되는가? </b> <br>
 <img width="380" alt="image" src="https://user-images.githubusercontent.com/83527046/215850048-2884b3e2-fbe5-4c2f-963b-10001490a1f8.png">
 
 <br>
 
## 프로그램 오류 출력

> <b> 1. 오류가 발생할 경우 오류 메시지를 정상적으로 출력하고 종료하는가? </b> <br>
 <img width="508" alt="image" src="https://user-images.githubusercontent.com/83527046/215850179-d46dc739-1abf-4a0b-b67b-f46f23569ee4.png">
  
 <br>
 
