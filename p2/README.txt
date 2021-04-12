// Name:    Jesse McCarville-Schueths
// Course:  4280
// Date:    April 11, 2021
// Project: P2

I assumed every test file ends with the extension ".ss21" 

BNF for p2:
<program>  ->     <vars> main <block>
<block>       ->      begin <vars> <stats> end
<vars>         ->      empty | data Identifier :=  Integer  ;  <vars> 
<expr>        ->      <N> - <expr>  | <N>
<N>             ->       <A> / <N> | <A> * <N> | <A>
<A>             ->        <M> + <A> | <M>
<M>              ->     * <M> |  <R>
<R>              ->      ( <expr> ) | Identifier | Integer
<stats>         ->      <stat>  <mStat>
<mStat>       ->      empty |  <stat>  <mStat>
<stat>           ->      <in> ;  | <out> ;  | <block> | <if> ;  | <loop> ;  | <assign> ; | <goto> ; | <label> ;
<in>              ->      getter  Identifier  
<out>            ->      outter <expr>
<if>               ->      if [ <expr> <RO> <expr> ] then <stat>
<loop>          ->      loop  [ <expr> <RO> <expr> ]  <stat>
<assign>       ->      assign Identifier  := <expr>  
<RO>            ->       =>  | =< |  ==  |   [ == ]  (three tokens)  | %
<label>          ->    void Identifier
<goto>           ->    proc Identifier
