# iniFile文件的使用

**字符集请修改为：多字节字符集**

**MFC的使用修改为：在共享DLL中使用MFC**

***

##ini文件格式

###节(section)

节用方括号括起来，单独占一行，例如：

[section]

###键(key)

键(key)又名属性(property)，单独占一行用等号连接键名和键值，例如：

name=value

###注释(comment)

注释使用英文分号（;）开头，单独占一行。在分号后面的文字，直到该行结尾都全部为注释，例如：

; comment text
