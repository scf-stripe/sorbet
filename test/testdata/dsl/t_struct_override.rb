# typed: true

class Override < T::Struct
  extend T::Sig

  prop :foo, String

  sig {params(foo: Integer).void}
  def initialize(foo:)
    @foo = foo.to_s
  end
end

Override.new # error: Missing required keyword argument `foo` for method `Override#initialize`
Override.new(foo: "no") # error: `String("no")` does not match `Integer` for argument `foo`
Override.new(foo: 3, bar: 4) # error: Unrecognized keyword argument `bar` passed for method `Override#initialize`
T.reveal_type(Override.new(foo: 3).foo) # error: Revealed type: `String`
