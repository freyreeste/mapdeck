#ifndef R_MAPDECK_PALETTE_H
#define R_MAPDECK_PALETTE_H

#include <Rcpp.h>
#include "R_mapdeck.hpp"
#include "mapdeck_defaults.hpp"


// [[Rcpp::depends(colourvalues)]]
#include "colourvalues/colours/colours_hex.hpp"


namespace mapdeck {
namespace palette {

  /*
   * resolve_palette
   * determines if the user supplied a palette, or should use default
   */
  inline SEXP resolve_palette( Rcpp::List& lst_params, Rcpp::List& params ) {

  	SEXP pal = mapdeck::defaults::default_palette;
  	int idx =  mapdeck::find_parameter_index( lst_params, "palette" );
  	//pal = idx >= 0 ? params[ idx ] : pal;

  	if (idx >= 0 ) {
  		// if function, evaluate it? (or do this in R before entering Rcpp?)
  		pal = params[ idx ];
  	}
  	return pal;
  }

  inline Rcpp::StringVector colour_with_palette(
  		SEXP& palette,
  		Rcpp::StringVector& fill_colour_vec,
  		Rcpp::NumericVector& alpha,
  		std::string& na_colour,
  		bool& include_alpha) {

  	switch ( TYPEOF( palette ) ) {
  	case 1: { // SYMSXP

  	// Rcpp::Symbol sym = Rcpp::as< Rcpp::Symbol >( pal );
  	// Rcpp::NumericMatrix thispal = Rcpp::as< Rcpp::NumericMatrix >( sym );
  	// hex_strings = colourvalues::colours_hex::colour_value_hex( fill_colour_vec, thispal, na_colour, include_alpha );
  	Rcpp::stop("Unsupported palette type");
  	break;
  }
  	case 14: { // REALSXP (i.e, matrix)
  		Rcpp::NumericMatrix thispal = Rcpp::as< Rcpp::NumericMatrix >( palette );
  		return colourvalues::colours_hex::colour_value_hex( fill_colour_vec, thispal, na_colour, include_alpha );
  		break;
  	}
  	case 16: {
  		std::string thispal = Rcpp::as< std::string>( palette );
  		return colourvalues::colours_hex::colour_value_hex( fill_colour_vec, thispal, na_colour, alpha, include_alpha );
  		break;
  	}
  	default: {
  		Rcpp::stop("Unsupported palette type");
  	}
  	}
  	return ""; // never reached
  }


	inline Rcpp::StringVector colour_with_palette(
			SEXP& palette,
			Rcpp::NumericVector& fill_colour_vec,
			Rcpp::NumericVector& alpha,
			std::string& na_colour,
			bool& include_alpha) {

		switch ( TYPEOF( palette ) ) {
		case 1: { // SYMSXP
		Rcpp::stop("Unsupported palette type");
		break;
	}
		case 14: { // REALSXP (i.e, matrix)
			Rcpp::NumericMatrix thispal = Rcpp::as< Rcpp::NumericMatrix >( palette );
			return colourvalues::colours_hex::colour_value_hex( fill_colour_vec, thispal, na_colour, include_alpha );
			break;
		}
		case 16: {
			std::string thispal = Rcpp::as< std::string>( palette );
			Rcpp::Rcout << "string palette " << thispal << std::endl;
			Rcpp::Rcout << fill_colour_vec << std::endl;
			Rcpp::Rcout << na_colour << std::endl;
			Rcpp::Rcout << alpha << std::endl;
			Rcpp::Rcout << include_alpha << std::endl;
			return colourvalues::colours_hex::colour_value_hex( fill_colour_vec, thispal, na_colour, alpha, include_alpha );
			break;
		}
		default: {
			Rcpp::stop("Unsupported palette type");
		}
		}
		return ""; // never reached
	}

} // namespace palette
} // namespace mapdeck

#endif
