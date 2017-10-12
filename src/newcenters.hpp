#ifndef NEW_CENTERS_HPP
#define NEW_CENTERS_HPP

#include <RcppArmadillo.h>
#include "warping.hpp"
#include "center_methods.hpp"


/// Compute new centers
/**
 * It's a function that handle the computation of new centers.
 */
arma::cube newCenters(const arma::mat& x_reg,
                      const arma::cube& y,
                      const arma::rowvec& x_out,
                      std::shared_ptr<Dissimilarity>& dissim,
                      std::shared_ptr<CenterMethod>& cen,
                      const arma::urowvec& par_opt,
                      cube& templates,
                      const urowvec& ict,
                      const urowvec& labels,
                      const bool show_iter
                     )
{
#ifdef _OPENMP // guard to check if openMP is available
    // switch to choose how to parallalelize
    // case 0 trivial  each thread one cluster
    //case 1 each cluster all the threads (available only with medoid)
    switch(par_opt(1))
    {
    case 0:
        #pragma omp parallel for num_threads(par_opt(0))
        for(uword i=0; i< ict.size(); i++)
        {
            urowvec sel = find(labels == ict(i)).t();
            center a = cen->computeCenter( x_reg.rows(sel), util::observations(y,sel), dissim, x_out );
            templates.tube(span(i),span::all) = a.y_center.t();
            #pragma omp critical
            {
                if(show_iter==true)
                    cout<<"The thread num. "<<omp_get_thread_num()<<" has computed template num. "<<i<<endl;
            }
        }
        break;
    case 1:

        for(uword i=0; i< ict.size(); i++)
        {
            urowvec sel = find(labels == ict(i)).t();
          cout<<"inizio calcolo centro"<<endl;
            center a = cen->computeParallelCenter( x_reg.rows(sel), util::observations(y,sel), dissim, x_out, par_opt(0));
            cout<<"finisco calcolo centro"<<endl;
            templates.tube(span(i),span::all) = a.y_center.t();
            if(show_iter==true)
                cout<<"Template num. "<<i<<" computed"<<endl;
        }
        break;
    }
#else
    // if OPENMP is not supported the execution is garantueed
    Rcpp::Rcout<<"OPENMP not supported"<<endl;
    for(uword i=0; i< ict.size(); i++)
    {
        urowvec sel = find(labels == ict(i)).t();
        center a = cen->computeCenter( x_reg.rows(sel), observations(y,sel), dissim, x_out ) ;
        templates.tube(span(i),span::all)= a.y_center.t();
        if(show_iter==true)
            cout<<"new template "<<i<<endl;//<<templates[i]<<endl;
    }
#endif
}// fine new centers
#endif
