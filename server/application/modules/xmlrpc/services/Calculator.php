<?php
class Xmlrpc_Service_Calculator
{
    /**
     * ２つの変数の合計を返します
     *
     * @param  int $x
     * @param  int $y
     * @return int
     */
    public function add($x, $y)
    {
        return $x + $y;
    }
 
    /**
     * ２つの変数の差を返します
     *
     * @param  int $x
     * @param  int $y
     * @return int
     */
    public function subtract($x, $y)
    {
        return $x - $y;
    }
 
    /**
     * ２つの変数の積を返します
     *
     * @param  int $x
     * @param  int $y
     * @return int
     */
    public function multiply($x, $y)
    {
        return $x * $y;
    }
 
    /**
     * ２つの変数の除算結果を返します
     *
     * @param  int $x
     * @param  int $y
     * @return float
     */
    public function divide($x, $y)
    {
        return $x / $y;
    }
}
