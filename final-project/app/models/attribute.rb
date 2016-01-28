class Attribute < ActiveRecord::Base
  belongs_to :entity
  has_many :measures
end
