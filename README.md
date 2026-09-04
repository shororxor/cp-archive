# Competitive Programming Code Archive

This is a local archive of my solution to a wide range of cp and dsa problems. My submissions are scattered across many online judges and sources, so I'm still trying to retrieve them after a very long time not doing cp.

All codes follow my speculated template which have tags for problem types, which facilitates searching and revision (using telescope in neovim). This storage is designated for internal and personal usage.

Format source code
```
find . -type f -name '*.cpp' -exec clang-format -i \
    --style='{IndentWidth: 4, TabWidth: 4, UseTab: Never}' {} +

find . -name '*.java' -exec clang-format -i \
  --style='{Language: Java, IndentWidth: 4, TabWidth: 4, UseTab: Never}' {} +
```
