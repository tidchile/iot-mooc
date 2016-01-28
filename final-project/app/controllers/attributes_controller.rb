class AttributesController < ApplicationController
  before_action :set_attribute, only: [:show, :update, :destroy]

  # GET /attributes
  # GET /attributes.json
  def index
    @attributes = Attribute.all

    render json: @attributes
  end

  # GET /attributes/1
  # GET /attributes/1.json
  def show
    render json: @attribute
  end

  # POST /attributes
  # POST /attributes.json
  def create
    @attribute = Attribute.new(attribute_params)

    if @attribute.save
      render json: @attribute, status: :created, location: @attribute
    else
      render json: @attribute.errors, status: :unprocessable_entity
    end
  end

  # PATCH/PUT /attributes/1
  # PATCH/PUT /attributes/1.json
  def update
    @attribute = Attribute.find(params[:id])

    if @attribute.update(attribute_params)
      head :no_content
    else
      render json: @attribute.errors, status: :unprocessable_entity
    end
  end

  # DELETE /attributes/1
  # DELETE /attributes/1.json
  def destroy
    @attribute.destroy

    head :no_content
  end

  private

    def set_attribute
      @attribute = Attribute.find(params[:id])
    end

    def attribute_params
      params.require(:attribute).permit(:entity_id, :name)
    end
end
