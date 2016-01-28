json.array!(@attributes) do |attribute|
  json.extract! attribute, :id, :entity_id, :name
  json.url attribute_url(attribute, format: :json)
end
