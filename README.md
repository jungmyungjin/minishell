# minishell
42seoul team project
🤝 (@ychoi, @mjung)

# ⚠️
### 라이브러리 설치 필요
`brew install readline`


### 라이브러리 심볼릭 링크 설정
`brew link --force readline`

### 파싱 문법
```
<pipeline>	     :	<cmd>
                 |	<pipeline> '|' <cmd>

<cmd>            :  <simple_cmd> 
						     |  <simple_cmd> <redirects>

<simple_cmd>     : <file_path>
                 : <argv>

<argv>           : <file_path> <args>

<redirects>      :             <io_redirect>
                 | <redirects> <io_redirect>


<io_redirect>    : '<'   <filename>
                 | '<<'  <filename>
                 | '>'   <filename>
                 | '>>'  <filename>

<args>           : WORD 
          			 | <args> WORD

<filename>       : WORD

<file_path>      : WORD
```


### Flow Chart 
![image](https://user-images.githubusercontent.com/17478634/135342473-05e6c6cd-9b3c-40ff-9a26-fb89cfc55db9.png)


### Tree Example
![image](https://user-images.githubusercontent.com/17478634/135342595-132f1dae-cf5b-4fda-bc26-1251363bfba0.png)
```ls -a -l >> a < b > c | grep "" | cat << x > y```

다음과 명령어가 오게될 경우 트리는 위와 같은 구조로 저장이 된다.









