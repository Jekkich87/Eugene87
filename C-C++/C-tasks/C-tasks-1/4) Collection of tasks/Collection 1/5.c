#include <stdio.h>

int main() {

    double m_ml, m_k, m_stak, n_kapvst, n_mlvst;

    int N_stak;

    m_ml=3e-23;

    m_k=0.05;

    m_stak=249.5;

    scanf("%d", &N_stak);

    n_kapvst=(m_stak/m_k)*N_stak;

    n_mlvst=(N_stak*m_stak)/3e-23;

    printf("%.0f %.3e", n_kapvst, n_mlvst);
  
    return 0;
    
}