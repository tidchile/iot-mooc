class Measure < ActiveRecord::Base
  belongs_to :entity_attribute, class_name: "Attribute"
end
