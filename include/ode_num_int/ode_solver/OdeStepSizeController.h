// OdeStepSizeController.h

#ifndef _ODESOLVER_ODESTEPSIZECONTROLLER_H_CF3E_424f_9766_BA04D388199F_
#define _ODESOLVER_ODESTEPSIZECONTROLLER_H_CF3E_424f_9766_BA04D388199F_

#include "def_prop_vd_template_class.h"
#include "factory.h"
#include "opt_param.h"

namespace ctm {
namespace math {

template< class VD >
using OdeStepSizeControllerObservers = cxx::Observers<
    const typename VD::value_type /*oldStepSize*/,
    const typename VD::value_type /*newStepSize*/,
    bool /*stepAccepted*/,
    bool /*stepSizeChanged*/ >;

template< class VD >
class OdeStepSizeController :
    public Factory< OdeStepSizeController<VD> >,
    public OptionalParameters
    {
    public:
        typedef VectorTemplate< VD > V;
        typedef typename VD::value_type real_type;

        struct Result
            {
            real_type newStepSize;
            bool acceptStep;
            bool changeStepSize;
            Result();
            Result(
                real_type newStepSize,
                bool acceptStep,
                bool changeStepSize ) :
                newStepSize( newStepSize ),
                acceptStep( acceptStep ),
                changeStepSize( changeStepSize )
                {}
            };

        OdeStepSizeControllerObservers<VD> odeStepSizeControllerObservers;

        virtual Result controlStepSize(
            real_type currentStepSize,
            real_type errorNorm,
            real_type methodOrder ) const = 0;
    };

CTM_DEF_NOTIFIED_PROP_VD_TEMPLATE_CLASS(
        OdeStepSizeControllerHolder, OdeStepSizeController,
        odeStepSizeController, setOdeStepSizeController,
        onOdeStepSizeControllerChanged, offOdeStepSizeControllerChanged )

} // end namespace math
} // end namespace ctm

#endif // _ODESOLVER_ODESTEPSIZECONTROLLER_H_CF3E_424f_9766_BA04D388199F_
