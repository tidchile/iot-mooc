json.array!(@measures) do |measure|
  json.extract! measure, :id, :attribute_id, :value
  json.url entity_attribute_measure_url(measure, format: :json)
end
