# exponential-tsp

Aluno: Victor José de Sousa Koehler

Matrícula: 20211023501



## Introdução

Neste trabalho são apresentadas implementações de modelos matemáticos para o Problema do Caixeiro-Viajante (do inglês, Travelling Salesman Problem), bem como algoritmos e estruturas auxiliares, como requisito da avaliação da disciplina de Tópicos Especiais do Programa de Pós-Graduação em Informática (PPGI) da Universidade Federal da Paraíba (UFPB). Esta implementação possui teor puramente educativo e não deve ser seriamente utilizada em ambientes de produção. Neste relatório são apresentados alguns resultados de experimentos computacionais realizados com esta implementação utilizando um conjunto de instâncias bem conhecido da literatura.

A Tabela a seguir relaciona as variantes dos algoritmos implementados. **DEPTH** descreve até qual profundidade da árvore de Branch&Cut os cortes fracionários são aplicados ao modelo; Se **DEPTH** = `s`, então a formulação do TSP usada é simétrica, do contrário, assimétrica. As colunas **MAXBACK_USERCUTS** e **MINCUT_USERCUTS** denotam a utilização da heurística *max-back* (Naddef et al.) e do algoritmo Stoer–Wagner de corte mínimo, respectivamente, nos cortes fracionários (*User callbacks*). **MINCUT_LAZIES** denota a utilização do algoritmo supracitado durante cortes inteiros (*Lazy callbacks*), se *False*, então é executado uma implementação simples baseada no algoritmo DFS para a detecção de ciclos. Por fim, a coluna **COMANDO BASE** descreve a respectiva linha de comando usada para a invocação do programa usando configuração descrita na linha.


| COMANDO BASE             | DEPTH   | MAXBACK_USERCUTS   | MINCUT_USERCUTS   | MINCUT_LAZIES   |
|:-------------------------|:--------|:-------------------|:------------------|:----------------|
| obj/mlCut -s             | s       | False              | False             | False           |
| obj/mlCut -d 4           | 4       | True               | True              | True            |
| obj/mlCut -d 4 -L        | 4       | True               | True              | False           |
| obj/mlCut -d 4 -S        | 4       | True               | False             | True            |
| obj/mlCut -d 4 -S -L     | 4       | True               | False             | False           |
| obj/mlCut -d 4 -N        | 4       | False              | True              | True            |
| obj/mlCut -d 4 -N -L     | 4       | False              | True              | False           |
| obj/mlCut -d 4 -N -S     | 4       | False              | False             | True            |
| obj/mlCut -d 4 -N -S -L  | 4       | False              | False             | False           |
| obj/mlCut -d 16          | 16      | True               | True              | True            |
| obj/mlCut -d 16 -L       | 16      | True               | True              | False           |
| obj/mlCut -d 16 -S       | 16      | True               | False             | True            |
| obj/mlCut -d 16 -S -L    | 16      | True               | False             | False           |
| obj/mlCut -d 16 -N       | 16      | False              | True              | True            |
| obj/mlCut -d 16 -N -L    | 16      | False              | True              | False           |
| obj/mlCut -d 16 -N -S    | 16      | False              | False             | True            |
| obj/mlCut -d 16 -N -S -L | 16      | False              | False             | False           |



A Tabela seguinte apresenta os experimentos computacionais realizados para avaliar o desempenho em termos de tempo de execução dos algoritmos implementados assim como descrito na tabela anterior.

<table>
  <thead>
    <tr>
      <th >&nbsp;</th>
      <th colspan="17">TIME ELAPSED</th>
    </tr>
    <tr>
      <th >DEPTH</th>
      <th colspan="8">16</th>
      <th colspan="8">4</th>
      <th >s</th>
    </tr>
    <tr>
      <th >MAXBACK_USERCUTS</th>
      <th colspan="4">False</th>
      <th colspan="4">True</th>
      <th colspan="4">False</th>
      <th colspan="4">True</th>
      <th >False</th>
    </tr>
    <tr>
      <th >MINCUT_USERCUTS</th>
      <th colspan="2">False</th>
      <th colspan="2">True</th>
      <th colspan="2">False</th>
      <th colspan="2">True</th>
      <th colspan="2">False</th>
      <th colspan="2">True</th>
      <th colspan="2">False</th>
      <th colspan="2">True</th>
      <th >False</th>
    </tr>
    <tr>
      <th >MINCUT_LAZIES</th>
      <th >False</th>
      <th >True</th>
      <th >False</th>
      <th >True</th>
      <th >False</th>
      <th >True</th>
      <th >False</th>
      <th >True</th>
      <th >False</th>
      <th >True</th>
      <th >False</th>
      <th >True</th>
      <th >False</th>
      <th >True</th>
      <th >False</th>
      <th >True</th>
      <th >False</th>
    </tr>
    <tr>
      <th >NAME</th>
      <th >&nbsp;</th>
      <th >&nbsp;</th>
      <th >&nbsp;</th>
      <th >&nbsp;</th>
      <th >&nbsp;</th>
      <th >&nbsp;</th>
      <th >&nbsp;</th>
      <th >&nbsp;</th>
      <th >&nbsp;</th>
      <th >&nbsp;</th>
      <th >&nbsp;</th>
      <th >&nbsp;</th>
      <th >&nbsp;</th>
      <th >&nbsp;</th>
      <th >&nbsp;</th>
      <th >&nbsp;</th>
      <th >&nbsp;</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th >cid5.tsp</th>
      <td >0.00</td>
      <td >0.01</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
    </tr>
    <tr>
      <th >cidp5.tsp</th>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.01</td>
      <td >0.00</td>
      <td >0.01</td>
      <td >0.00</td>
      <td >0.01</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
    </tr>
    <tr>
      <th >test10.tsp</th>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
    </tr>
    <tr>
      <th >burma14.tsp</th>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
    </tr>
    <tr>
      <th >ulysses16.tsp</th>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.01</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.01</td>
      <td >0.01</td>
      <td >0.00</td>
    </tr>
    <tr>
      <th >gr17.tsp</th>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.01</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
    </tr>
    <tr>
      <th >gr21.tsp</th>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
    </tr>
    <tr>
      <th >ulysses22.tsp</th>
      <td >0.01</td>
      <td >0.01</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.01</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.01</td>
      <td >0.00</td>
      <td >0.01</td>
      <td >0.00</td>
      <td >0.01</td>
      <td >0.01</td>
    </tr>
    <tr>
      <th >gr24.tsp</th>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.01</td>
      <td >0.00</td>
      <td >0.01</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.01</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.02</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.01</td>
      <td >0.00</td>
      <td >0.01</td>
    </tr>
    <tr>
      <th >fri26.tsp</th>
      <td >0.01</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.01</td>
      <td >0.01</td>
      <td >0.01</td>
      <td >0.00</td>
      <td >0.01</td>
      <td >0.00</td>
      <td >0.01</td>
      <td >0.00</td>
      <td >0.01</td>
      <td >0.01</td>
      <td >0.00</td>
      <td >0.00</td>
      <td >0.01</td>
      <td >0.02</td>
    </tr>
    <tr>
      <th >bayg29.tsp</th>
      <td >0.01</td>
      <td >0.01</td>
      <td >0.01</td>
      <td >0.01</td>
      <td >0.01</td>
      <td >0.01</td>
      <td >0.01</td>
      <td >0.01</td>
      <td >0.00</td>
      <td >0.02</td>
      <td >0.01</td>
      <td >0.00</td>
      <td >0.02</td>
      <td >0.01</td>
      <td >0.02</td>
      <td >0.01</td>
      <td >3.93</td>
    </tr>
    <tr>
      <th >bays29.tsp</th>
      <td >0.01</td>
      <td >0.00</td>
      <td >0.01</td>
      <td >0.02</td>
      <td >0.01</td>
      <td >0.02</td>
      <td >0.01</td>
      <td >0.02</td>
      <td >0.01</td>
      <td >0.02</td>
      <td >0.01</td>
      <td >0.01</td>
      <td >0.01</td>
      <td >0.03</td>
      <td >0.01</td>
      <td >0.02</td>
      <td >6.29</td>
    </tr>
    <tr>
      <th >dantzig42.tsp</th>
      <td >0.02</td>
      <td >0.04</td>
      <td >0.04</td>
      <td >0.06</td>
      <td >0.04</td>
      <td >0.04</td>
      <td >0.05</td>
      <td >0.03</td>
      <td >0.03</td>
      <td >0.04</td>
      <td >0.04</td>
      <td >0.07</td>
      <td >0.05</td>
      <td >0.04</td>
      <td >0.05</td>
      <td >0.04</td>
      <td >13.49</td>
    </tr>
    <tr>
      <th >swiss42.tsp</th>
      <td >0.01</td>
      <td >0.01</td>
      <td >0.01</td>
      <td >0.02</td>
      <td >0.04</td>
      <td >0.04</td>
      <td >0.03</td>
      <td >0.04</td>
      <td >0.01</td>
      <td >0.02</td>
      <td >0.02</td>
      <td >0.02</td>
      <td >0.03</td>
      <td >0.04</td>
      <td >0.04</td>
      <td >0.04</td>
      <td >5.53</td>
    </tr>
    <tr>
      <th >att48.tsp</th>
      <td >0.07</td>
      <td >1.30</td>
      <td >0.06</td>
      <td >1.80</td>
      <td >0.05</td>
      <td >4.65</td>
      <td >0.07</td>
      <td >1.39</td>
      <td >0.07</td>
      <td >1.48</td>
      <td >0.07</td>
      <td >2.74</td>
      <td >0.06</td>
      <td >4.92</td>
      <td >0.06</td>
      <td >1.15</td>
      <td >8.76</td>
    </tr>
    <tr>
      <th >hk48.tsp</th>
      <td >0.01</td>
      <td >0.03</td>
      <td >0.02</td>
      <td >0.05</td>
      <td >0.02</td>
      <td >0.03</td>
      <td >0.02</td>
      <td >0.03</td>
      <td >0.03</td>
      <td >0.03</td>
      <td >0.02</td>
      <td >0.04</td>
      <td >0.01</td>
      <td >0.02</td>
      <td >0.02</td>
      <td >0.03</td>
      <td >5.13</td>
    </tr>
    <tr>
      <th >eil51.tsp</th>
      <td >0.05</td>
      <td >0.08</td>
      <td >0.04</td>
      <td >0.05</td>
      <td >0.06</td>
      <td >0.05</td>
      <td >0.06</td>
      <td >0.06</td>
      <td >0.06</td>
      <td >0.10</td>
      <td >0.05</td>
      <td >0.04</td>
      <td >0.05</td>
      <td >0.05</td>
      <td >0.05</td>
      <td >0.05</td>
      <td >6.75</td>
    </tr>
    <tr>
      <th >berlin52.tsp</th>
      <td >0.02</td>
      <td >0.03</td>
      <td >0.02</td>
      <td >0.03</td>
      <td >0.02</td>
      <td >0.02</td>
      <td >0.02</td>
      <td >0.02</td>
      <td >0.02</td>
      <td >0.03</td>
      <td >0.02</td>
      <td >0.02</td>
      <td >0.03</td>
      <td >0.02</td>
      <td >0.03</td>
      <td >0.02</td>
      <td >0.03</td>
    </tr>
    <tr>
      <th >brazil58.tsp</th>
      <td >0.05</td>
      <td >0.30</td>
      <td >0.08</td>
      <td >0.16</td>
      <td >0.18</td>
      <td >11.52</td>
      <td >0.22</td>
      <td >0.24</td>
      <td >0.05</td>
      <td >0.30</td>
      <td >0.08</td>
      <td >0.17</td>
      <td >0.17</td>
      <td >9.30</td>
      <td >0.21</td>
      <td >0.23</td>
      <td >0.19</td>
    </tr>
    <tr>
      <th >st70.tsp</th>
      <td >0.17</td>
      <td >0.10</td>
      <td >0.17</td>
      <td >0.10</td>
      <td >0.13</td>
      <td >0.17</td>
      <td >0.14</td>
      <td >0.10</td>
      <td >0.18</td>
      <td >0.10</td>
      <td >0.17</td>
      <td >0.09</td>
      <td >0.13</td>
      <td >0.14</td>
      <td >0.14</td>
      <td >0.09</td>
      <td >7.77</td>
    </tr>
    <tr>
      <th >eil76.tsp</th>
      <td >0.05</td>
      <td >0.05</td>
      <td >0.09</td>
      <td >0.05</td>
      <td >0.06</td>
      <td >0.05</td>
      <td >0.08</td>
      <td >0.05</td>
      <td >0.06</td>
      <td >0.05</td>
      <td >0.09</td>
      <td >0.05</td>
      <td >0.06</td>
      <td >0.06</td>
      <td >0.07</td>
      <td >0.06</td>
      <td >8.96</td>
    </tr>
    <tr>
      <th >pr76.tsp</th>
      <td >48.20</td>
      <td >217.50</td>
      <td >17.78</td>
      <td >22.64</td>
      <td >87.95</td>
      <td >270.86</td>
      <td >146.48</td>
      <td >60.22</td>
      <td >49.59</td>
      <td >209.79</td>
      <td >50.72</td>
      <td >65.18</td>
      <td >104.34</td>
      <td >158.55</td>
      <td >225.48</td>
      <td >62.01</td>
      <td >66.60</td>
    </tr>
    <tr>
      <th >rat99.tsp</th>
      <td >0.40</td>
      <td >0.32</td>
      <td >0.22</td>
      <td >0.29</td>
      <td >0.20</td>
      <td >0.24</td>
      <td >0.19</td>
      <td >0.25</td>
      <td >0.35</td>
      <td >0.32</td>
      <td >0.23</td>
      <td >0.25</td>
      <td >0.21</td>
      <td >0.24</td>
      <td >0.19</td>
      <td >0.23</td>
      <td >7.11</td>
    </tr>
    <tr>
      <th >rd100.tsp</th>
      <td >21.60</td>
      <td >3.03</td>
      <td >0.55</td>
      <td >0.74</td>
      <td >0.74</td>
      <td >5.89</td>
      <td >0.41</td>
      <td >1.05</td>
      <td >7.03</td>
      <td >5.25</td>
      <td >0.54</td>
      <td >0.82</td>
      <td >0.68</td>
      <td >6.74</td>
      <td >0.40</td>
      <td >1.07</td>
      <td >6.51</td>
    </tr>
    <tr>
      <th >eil101.tsp</th>
      <td >0.20</td>
      <td >0.47</td>
      <td >0.22</td>
      <td >0.25</td>
      <td >0.20</td>
      <td >0.37</td>
      <td >0.20</td>
      <td >0.50</td>
      <td >0.20</td>
      <td >0.73</td>
      <td >0.22</td>
      <td >0.24</td>
      <td >0.20</td>
      <td >0.37</td>
      <td >0.19</td>
      <td >0.54</td>
      <td >0.66</td>
    </tr>
    <tr>
      <th >lin105.tsp</th>
      <td >1.00</td>
      <td >0.64</td>
      <td >0.56</td>
      <td >0.65</td>
      <td >0.29</td>
      <td >1.04</td>
      <td >0.29</td>
      <td >1.04</td>
      <td >1.16</td>
      <td >0.62</td>
      <td >0.60</td>
      <td >0.67</td>
      <td >0.30</td>
      <td >1.15</td>
      <td >0.32</td>
      <td >1.04</td>
      <td >2.92</td>
    </tr>
    <tr>
      <th >pr107.tsp</th>
      <td >0.05</td>
      <td >0.99</td>
      <td >0.04</td>
      <td >0.75</td>
      <td >0.05</td>
      <td >0.50</td>
      <td >0.04</td>
      <td >0.48</td>
      <td >0.05</td>
      <td >0.87</td>
      <td >0.05</td>
      <td >0.81</td>
      <td >0.04</td>
      <td >0.50</td>
      <td >0.04</td>
      <td >0.47</td>
      <td >0.36</td>
    </tr>
    <tr>
      <th >gr137.tsp</th>
      <td >1.89</td>
      <td >1.04</td>
      <td >1.61</td>
      <td >2.64</td>
      <td >5.28</td>
      <td >2.38</td>
      <td >2.58</td>
      <td >1.84</td>
      <td >1.43</td>
      <td >1.03</td>
      <td >1.36</td>
      <td >2.30</td>
      <td >4.94</td>
      <td >2.29</td>
      <td >2.22</td>
      <td >1.56</td>
      <td >23.90</td>
    </tr>
    <tr>
      <th >pr144.tsp</th>
      <td >3.86</td>
      <td >16.22</td>
      <td >4.60</td>
      <td >4.84</td>
      <td >3.38</td>
      <td >6.88</td>
      <td >3.59</td>
      <td >5.16</td>
      <td >4.73</td>
      <td >15.77</td>
      <td >2.81</td>
      <td >3.48</td>
      <td >3.23</td>
      <td >10.99</td>
      <td >3.68</td>
      <td >5.01</td>
      <td >9.90</td>
    </tr>
    <tr>
      <th >ch150.tsp</th>
      <td >8.37</td>
      <td >6.62</td>
      <td >4.23</td>
      <td >4.41</td>
      <td >8.47</td>
      <td >4.25</td>
      <td >5.84</td>
      <td >5.28</td>
      <td >3.80</td>
      <td >7.86</td>
      <td >2.99</td>
      <td >3.18</td>
      <td >2.80</td>
      <td >4.06</td>
      <td >5.58</td>
      <td >5.11</td>
      <td >33.28</td>
    </tr>
    <tr>
      <th >kroA150.tsp</th>
      <td >18.12</td>
      <td >9.64</td>
      <td >3.48</td>
      <td >6.52</td>
      <td >8.61</td>
      <td >10.69</td>
      <td >6.51</td>
      <td >9.31</td>
      <td >11.65</td>
      <td >8.46</td>
      <td >2.85</td>
      <td >6.49</td>
      <td >3.50</td>
      <td >6.07</td>
      <td >5.22</td>
      <td >9.35</td>
      <td >42.16</td>
    </tr>
    <tr>
      <th >pr152.tsp</th>
      <td >2.19</td>
      <td >77.58</td>
      <td >3.90</td>
      <td >7.98</td>
      <td >4.34</td>
      <td >9.67</td>
      <td >5.26</td>
      <td >8.32</td>
      <td >1.98</td>
      <td >71.36</td>
      <td >2.64</td>
      <td >4.15</td>
      <td >3.04</td>
      <td >14.94</td>
      <td >3.23</td>
      <td >5.92</td>
      <td >12.24</td>
    </tr>
    <tr>
      <th >si175.tsp</th>
      <td >14.49</td>
      <td >67.38</td>
      <td >23.87</td>
      <td >14.27</td>
      <td >44.46</td>
      <td >26.22</td>
      <td >19.23</td>
      <td >17.24</td>
      <td >21.06</td>
      <td >40.32</td>
      <td >14.87</td>
      <td >26.00</td>
      <td >24.77</td>
      <td >12.02</td>
      <td >16.27</td>
      <td >17.17</td>
      <td >601.74</td>
    </tr>
    <tr>
      <th >brg180.tsp</th>
      <td >1.03</td>
      <td >8.58</td>
      <td >0.82</td>
      <td >1.49</td>
      <td >2.35</td>
      <td >4.80</td>
      <td >0.71</td>
      <td >12.27</td>
      <td >0.98</td>
      <td >8.73</td>
      <td >0.78</td>
      <td >1.51</td>
      <td >2.16</td>
      <td >5.35</td>
      <td >0.74</td>
      <td >8.89</td>
      <td >3.72</td>
    </tr>
    <tr>
      <th >rat195.tsp</th>
      <td >38.17</td>
      <td >68.55</td>
      <td >45.09</td>
      <td >22.19</td>
      <td >43.86</td>
      <td >70.43</td>
      <td >18.18</td>
      <td >46.95</td>
      <td >36.39</td>
      <td >72.61</td>
      <td >12.80</td>
      <td >28.41</td>
      <td >80.59</td>
      <td >46.47</td>
      <td >12.85</td>
      <td >18.49</td>
      <td >602.16</td>
    </tr>
    <tr>
      <th >d198.tsp</th>
      <td >9.33</td>
      <td >376.17</td>
      <td >34.80</td>
      <td >14.21</td>
      <td >24.91</td>
      <td >24.36</td>
      <td >21.91</td>
      <td >30.18</td>
      <td >9.05</td>
      <td >380.11</td>
      <td >23.19</td>
      <td >10.53</td>
      <td >21.25</td>
      <td >38.16</td>
      <td >21.13</td>
      <td >25.38</td>
      <td >94.49</td>
    </tr>
    <tr>
      <th >gr202.tsp</th>
      <td >13.45</td>
      <td >17.73</td>
      <td >8.87</td>
      <td >9.87</td>
      <td >4.71</td>
      <td >25.52</td>
      <td >9.05</td>
      <td >18.69</td>
      <td >13.69</td>
      <td >18.09</td>
      <td >7.19</td>
      <td >6.29</td>
      <td >4.15</td>
      <td >22.91</td>
      <td >6.15</td>
      <td >14.22</td>
      <td >12.81</td>
    </tr>
    <tr>
      <th >pr226.tsp</th>
      <td >12.73</td>
      <td >39.02</td>
      <td >13.80</td>
      <td >20.53</td>
      <td >13.80</td>
      <td >17.16</td>
      <td >21.70</td>
      <td >31.41</td>
      <td >12.42</td>
      <td >38.36</td>
      <td >10.07</td>
      <td >18.16</td>
      <td >13.30</td>
      <td >32.87</td>
      <td >21.82</td>
      <td >14.43</td>
      <td >13.79</td>
    </tr>
    <tr>
      <th >pr264.tsp</th>
      <td >8.72</td>
      <td >186.66</td>
      <td >7.61</td>
      <td >9.89</td>
      <td >14.30</td>
      <td >24.11</td>
      <td >35.89</td>
      <td >14.61</td>
      <td >8.27</td>
      <td >200.42</td>
      <td >10.27</td>
      <td >10.32</td>
      <td >13.44</td>
      <td >35.39</td>
      <td >24.28</td>
      <td >15.35</td>
      <td >24.38</td>
    </tr>
    <tr>
      <th >a280.tsp</th>
      <td >2.94</td>
      <td >5.95</td>
      <td >6.10</td>
      <td >5.92</td>
      <td >15.51</td>
      <td >16.02</td>
      <td >18.28</td>
      <td >17.86</td>
      <td >3.43</td>
      <td >6.08</td>
      <td >6.07</td>
      <td >5.68</td>
      <td >15.13</td>
      <td >14.74</td>
      <td >18.72</td>
      <td >15.24</td>
      <td >225.09</td>
    </tr>
    <tr>
      <th >lin318.tsp</th>
      <td >47.96</td>
      <td >651.15</td>
      <td >69.53</td>
      <td >43.11</td>
      <td >30.71</td>
      <td >122.38</td>
      <td >54.29</td>
      <td >123.72</td>
      <td >44.96</td>
      <td >953.07</td>
      <td >29.92</td>
      <td >45.29</td>
      <td >21.91</td>
      <td >228.93</td>
      <td >76.06</td>
      <td >160.77</td>
      <td >606.74</td>
    </tr>
    <tr>
      <th >linhp318.tsp</th>
      <td >46.60</td>
      <td >653.93</td>
      <td >66.53</td>
      <td >43.32</td>
      <td >29.24</td>
      <td >122.37</td>
      <td >48.96</td>
      <td >118.57</td>
      <td >44.83</td>
      <td >663.22</td>
      <td >30.52</td>
      <td >45.14</td>
      <td >23.58</td>
      <td >229.42</td>
      <td >53.66</td>
      <td >125.77</td>
      <td >605.51</td>
    </tr>
    <tr>
      <th >pa561.tsp</th>
      <td >1070.15</td>
      <td >794.88</td>
      <td >691.30</td>
      <td >711.97</td>
      <td >534.23</td>
      <td >546.13</td>
      <td >557.41</td>
      <td >540.87</td>
      <td >869.64</td>
      <td >782.16</td>
      <td >745.51</td>
      <td >797.42</td>
      <td >559.22</td>
      <td >551.07</td>
      <td >553.55</td>
      <td >539.31</td>
      <td >580.59</td>
    </tr>
    <tr>
      <th >rat575.tsp</th>
      <td >729.56</td>
      <td >744.03</td>
      <td >598.79</td>
      <td >606.68</td>
      <td >667.46</td>
      <td >606.24</td>
      <td >612.81</td>
      <td >538.90</td>
      <td >726.02</td>
      <td >741.11</td>
      <td >685.38</td>
      <td >740.34</td>
      <td >761.09</td>
      <td >684.34</td>
      <td >704.28</td>
      <td >649.03</td>
      <td >602.26</td>
    </tr>
    <tr>
      <th >TOTAL</th>
      <td >2101.50</td>
      <td >3950.05</td>
      <td >1604.87</td>
      <td >1557.53</td>
      <td >1545.69</td>
      <td >1935.13</td>
      <td >1590.53</td>
      <td >1606.73</td>
      <td >1873.24</td>
      <td >4228.54</td>
      <td >1642.16</td>
      <td >1825.96</td>
      <td >1664.50</td>
      <td >2122.21</td>
      <td >1756.78</td>
      <td >1698.13</td>
      <td >4245.79</td>
    </tr>
  </tbody>
</table>

