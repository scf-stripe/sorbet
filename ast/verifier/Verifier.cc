#include "verifier.h"
#include "ast/treemap/treemap.h"

using namespace std;
namespace sorbet::ast {

class VerifierWalker {
public:
    unique_ptr<Expression> preTransformExpression(core::MutableContext ctx, unique_ptr<Expression> original) {
        if (!isa_tree<EmptyTree>(original.get())) {
            ENFORCE(original->loc.exists(), "location is unset");
        }

        original->_sanityCheck();

        return original;
    }
};

unique_ptr<Expression> Verifier::run(core::MutableContext ctx, unique_ptr<Expression> node) {
    if (!debug_mode) {
        return node;
    }
    VerifierWalker vw;
    return TreeMap::apply(ctx, vw, move(node));
}

} // namespace sorbet::ast