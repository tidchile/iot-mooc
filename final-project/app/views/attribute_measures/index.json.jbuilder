json.array!(@attribute_measures) do |attribute_measure|
  json.extract! attribute_measure, :id, :attribute_id, :value
  json.url attribute_measure_url(attribute_measure, format: :json)
end
