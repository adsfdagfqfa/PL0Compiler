package org.example.antlr.PL0;

import lombok.Data;

@Data
public class Quadruple {//中间代码指令
    String insType;//操作类型
    String arg1 ;//操作数1
    String arg2 ;//操作数2
    String result;//结果
    Quadruple() {//构造参数
        arg1 = "_";
        arg2 = "_";
        result = "_";
    }
}
