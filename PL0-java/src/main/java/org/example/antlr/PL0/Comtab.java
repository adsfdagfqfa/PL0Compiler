package org.example.antlr.PL0;

import lombok.Data;

@Data
public class Comtab {
    String name;//名字
    Integer kind;//种类,0表示常量，1表示变量
    Integer value;//数值
}
