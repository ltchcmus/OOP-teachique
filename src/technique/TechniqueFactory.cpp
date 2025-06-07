#include "TechniqueFactory.h"
#include "StructuredBindings.h"
#include "IfConstexpr.h"
#include "OptionalTechnique.h"
#include "VariantTechnique.h"
#include "AnyTechnique.h"
#include "FilesystemTechnique.h"
#include "StringViewTechnique.h"
#include "FoldExprTechnique.h"
#include "InlineVarTechnique.h"
#include "SharedMutexTechnique.h"
#include "ConceptsTechnique.h"
#include "RangesTechnique.h"
#include "CoroutinesTechnique.h"
#include "SpanTechnique.h"
#include "SpaceshipTechnique.h"
#include "FormatTechnique.h"
#include "DeducingThisTechnique.h"
#include "PrintTechnique.h"
#include "ExpectedTechnique.h"
#include <vector>
#include <memory>

std::vector<std::unique_ptr<ITechnique>> TechniqueFactory::createAll() {
    std::vector<std::unique_ptr<ITechnique>> v;
    v.push_back(std::make_unique<StructuredBindings>());
    v.push_back(std::make_unique<IfConstexpr>());
    v.push_back(std::make_unique<OptionalTechnique>());
    v.push_back(std::make_unique<VariantTechnique>());
    v.push_back(std::make_unique<AnyTechnique>());
    v.push_back(std::make_unique<FilesystemTechnique>());
    v.push_back(std::make_unique<StringViewTechnique>());
    v.push_back(std::make_unique<FoldExprTechnique>());
    v.push_back(std::make_unique<InlineVarTechnique>());
    v.push_back(std::make_unique<SharedMutexTechnique>());
    v.push_back(std::make_unique<ConceptsTechnique>());
    v.push_back(std::make_unique<RangesTechnique>());
    v.push_back(std::make_unique<CoroutinesTechnique>());
    v.push_back(std::make_unique<SpanTechnique>());
    v.push_back(std::make_unique<SpaceshipTechnique>());
    v.push_back(std::make_unique<FormatTechnique>());
    v.push_back(std::make_unique<ExpectedTechnique>());
    v.push_back(std::make_unique<DeducingThisTechnique>());
    v.push_back(std::make_unique<PrintTechnique>());
    return v;
}