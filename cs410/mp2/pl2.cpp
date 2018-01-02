/**
 * @file pl2.cpp
 * @author CS 410 Spring 2016
 */

#include "meta/index/inverted_index.h"
#include "meta/index/ranker/pl2.h"
#include "meta/index/score_data.h"
#include "meta/math/fastapprox.h"

namespace meta
{
namespace index
{

const util::string_view pl2::id = "pl2";
const constexpr float pl2::default_c;

pl2::pl2(float c) : c_{c}
{
    // nothing
}

pl2::pl2(std::istream& in) : c_{io::packed::read<float>(in)}
{
    // nothing
}

void pl2::save(std::ostream& out) const
{
    io::packed::write(out, id);
    io::packed::write(out, c_);
}


float pl2::score_one(const score_data& sd)
{
    // TODO implement this function!
    float avg_dl = sd.avg_dl;
    float c = c_;
    float tfn = (float)(sd.doc_term_count) * (float)fastapprox::fastlog2(1.0 + (float)c * (float)(avg_dl / (float)sd.doc_size));
    float lambda = (float)sd.num_docs/(float)sd.corpus_term_count;
    
    if(lambda < 1 || tfn <= 0)
    {
    	return 0.0;
    }
    
    // splits the summation into three parts separated by addition
    float cttQ = (float)sd.query_term_weight;
    float score1 = (float)((float)tfn * (float)fastapprox::fastlog2(tfn * lambda));
    float score2 = (float)fastapprox::fastlog2(e_) * ((float)(1.0/lambda) - (float)tfn);
    float score3 = (float) (0.5 * (float)(fastapprox::fastlog2(2.0 * (float)pi_ * (float)tfn)));
    float score_num = cttQ * (score1 + score2 + score3);
    float score = score_num / ((float)((float)tfn + 1.0));
    
    return score;

}

template <>
std::unique_ptr<ranker> make_ranker<pl2>(const cpptoml::table& config)
{
    auto c = config.get_as<double>("c").value_or(pl2::default_c);
    return make_unique<pl2>(c);
}
}
}
