class EntitiesController < ApplicationController
  before_action :set_entity, only: [:show, :update, :destroy]

  # GET /entities
  # GET /entities.json
  def index
    @entities = Entity.all

    render json: @entities
  end

  # GET /entities/1
  # GET /entities/1.json
  def show
    render json: @entity
  end

  # POST /entities
  # POST /entities.json
  def create
    @entity = Entity.new(entity_params)

    if @entity.save
      render json: @entity, status: :created, location: @entity
    else
      render json: @entity.errors, status: :unprocessable_entity
    end
  end

  # PATCH/PUT /entities/1
  # PATCH/PUT /entities/1.json
  def update
    @entity = Entity.find(params[:id])

    if @entity.update(entity_params)
      head :no_content
    else
      render json: @entity.errors, status: :unprocessable_entity
    end
  end

  # DELETE /entities/1
  # DELETE /entities/1.json
  def destroy
    @entity.destroy

    head :no_content
  end

  private

    def set_entity
      @entity = Entity.find(params[:id])
    end

    def entity_params
      params.require(:entity).permit(:name, :type)
    end
end
